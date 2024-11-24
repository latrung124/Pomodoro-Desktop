/*
* GoogleOAuth.cpp
* Author: Trung La
* Date: 2024-11-24
* This is an implementation class for Google OAuth authentication provider
*/

#include "GoogleOAuth.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

#include <QUrlQuery>
#include <QNetworkRequest>
#include <QTcpSocket>
#include <QRegularExpression>
#include <QNetworkReply>

#include <QDesktopServices>

#include <iostream>
#include <fstream>
#include <string>

GoogleOAuth::GoogleOAuth(QObject *parent)
    : QObject(parent)
    , m_isConfigAvailable(false)
    , m_tcpServer(nullptr)
{
    if (m_isConfigAvailable = loadConfig(); !m_isConfigAvailable) {
        std::cerr << "Failed to load Google OAuth config" << std::endl;
    }
}

bool GoogleOAuth::requestAccessToken()
{
    if (!m_isConfigAvailable) {
        std::cerr << "Google OAuth config is not available" << std::endl;
        return false;
    }

    std::cout << "Requesting authorization code from Google..." << std::endl;
    QUrl authUrl(QString::fromStdString(generateAuthorizationUrl()));
    QUrlQuery query(authUrl);
    authUrl.setQuery(query);
    QDesktopServices::openUrl(authUrl);

    m_tcpServer = new QTcpServer();
    if (m_tcpServer->listen(QHostAddress::LocalHost, 8080)) {
        std::cout << "Listening on port 8080 for authorization code..." << std::endl;

        auto responseHandler = [this]() {
            QTcpSocket *client = m_tcpServer->nextPendingConnection();
            client->waitForReadyRead();
            QString response = client->readAll();

            // Extract the authorization code from the URL
            QStringList lines = response.split("\r\n");
            QString firstLine = lines.first();
            QRegularExpression codeRegex("code=([^&\\s]+)");
            QRegularExpressionMatch match = codeRegex.match(firstLine);
            if (match.hasMatch()) {
                QString authorizationCode = match.captured(1);
                qDebug() << "Authorization Code:" << authorizationCode;

                // Respond to the browser
                client->write("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                              "<html><body><h1>Authorization Successful</h1>"
                              "<p>You can close this window.</p></body></html>");
                client->disconnectFromHost();

                // Pass the code to the next step
                if (exchangeCodeForToken(authorizationCode.toStdString())) {
                    std::cout << "Successfully exchanged authorization code for access token" << std::endl;
                } else {
                    std::cerr << "Failed to exchange authorization code for access token" << std::endl;
                }
            } else {
                std::cerr << "Failed to extract authorization code" << std::endl;
            }

            client->close();
            client->deleteLater();
            m_tcpServer->close();
            m_tcpServer->deleteLater();
        };

        QObject::connect(m_tcpServer, &QTcpServer::newConnection, responseHandler);
    } else {
        std::cerr << "Failed to listen on port 8080" << std::endl;
        return false;
    }

    return true;
}

bool GoogleOAuth::exchangeCodeForToken(const std::string &authorizationCode)
{
    if (!m_isConfigAvailable) {
        std::cerr << "Google OAuth config is not available" << std::endl;
        return false;
    }

    std::cout << "Exchanging authorization code for access token..." << std::endl;
    QUrl tokenUrl(QString::fromStdString(m_oauthConfig.tokenUri));
    QNetworkRequest request(tokenUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery postData;
    postData.addQueryItem("code", QString::fromStdString(authorizationCode));
    postData.addQueryItem("client_id", QString::fromStdString(m_oauthConfig.clientId));
    postData.addQueryItem("client_secret", QString::fromStdString(m_oauthConfig.clientSecret));
    postData.addQueryItem("redirect_uri", QString::fromStdString(m_oauthConfig.redirectUri + ":8080"));
    postData.addQueryItem("grant_type", "authorization_code");

    m_networkManager.post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

    auto replyHandler = [this](QNetworkReply *reply) {
        if (reply->error() != QNetworkReply::NoError) {
            std::cerr << "Failed to exchange authorization code for access token" << std::endl;
            return;
        }

        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();
        std::string accessToken = jsonObj["access_token"].toString().toStdString();
        std::cout << "Access Token: " << accessToken << std::endl;

        m_googleAccessToken.accessToken = accessToken;
        m_googleAccessToken.tokenType = jsonObj["token_type"].toString().toStdString();
        m_googleAccessToken.expiresIn = jsonObj["expires_in"].toString().toStdString();
        m_googleAccessToken.refreshToken = jsonObj["refresh_token"].toString().toStdString();
        m_googleAccessToken.scope = jsonObj["scope"].toString().toStdString();

        reply->deleteLater();
    };

    QObject::connect(&m_networkManager, &QNetworkAccessManager::finished, replyHandler);

    return true;
}

bool GoogleOAuth::loadConfig()
{
    try {
        std::ifstream configFile(std::string(FIREBASE_CONFIG_PATH) + "/client_secret_desktop.json");
        if (!configFile.is_open()) {
            std::cerr << "Failed to open Google OAuth config file" << std::endl;
            return false;
        }

        std::string configJsonStr = std::string((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());
        QJsonDocument jsonDoc = QJsonDocument::fromJson(configJsonStr.c_str());
        QJsonObject jsonObj = jsonDoc.object();
        QJsonObject installedObj = jsonObj["installed"].toObject();

        m_oauthConfig = {
            .clientId = installedObj["client_id"].toString().toStdString(),
            .projectId = installedObj["project_id"].toString().toStdString(),
            .clientSecret = installedObj["client_secret"].toString().toStdString(),
            .redirectUri = installedObj["redirect_uris"].toArray()[0].toString().toStdString(),
            .authUri = installedObj["auth_uri"].toString().toStdString(),
            .tokenUri = installedObj["token_uri"].toString().toStdString(),
            .platform = "desktop",
        };
    } catch (const std::exception& e) {
        std::cerr << "Exception load config: " << e.what() << std::endl;
        return false;
    }

    return true;
}

std::string GoogleOAuth::generateAuthorizationUrl()
{
    using namespace firebase_utils::authentication;

    std::string authorizationUrl = m_oauthConfig.authUri + "?";
    authorizationUrl += gGoogleOAuthScope + "&";
    authorizationUrl += gGoogleOAuthResponseType + "&";
    authorizationUrl += gGoogleOAuthState + "&";
    authorizationUrl += m_oauthConfig.redirectUri + ":8080" + "&";
    authorizationUrl += "client_id=" + m_oauthConfig.clientId;
    std::cout << "Authorization URL: " << authorizationUrl << std::endl;

    return authorizationUrl;
}