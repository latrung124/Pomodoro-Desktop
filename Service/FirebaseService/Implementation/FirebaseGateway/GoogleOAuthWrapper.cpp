/*
* OAuthWrapper.cpp
* Author: Trung La
* Date: 2024-12-10
* This is a wrapper class for OAuth authentication providers
*/

#include "FirebaseGateway/GoogleOAuthWrapper.h"

#include <QNetworkReply>
#include <QDesktopServices>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include <fstream>

GoogleOAuthWrapper::GoogleOAuthWrapper(QObject* parent)
    : OAuthWrapper(parent)
    , m_tcpServer(nullptr)
    , m_loadedConfig(false)
{
    m_loadedConfig = loadConfig();
}

GoogleOAuthWrapper::~GoogleOAuthWrapper()
{
}

void GoogleOAuthWrapper::signIn()
{
    if (!m_loadedConfig) {
        return;
    }

    if (!openListenServer()) {
        return;
    }

    if (!requestAccessToken()) {
        return;
    }
}

bool GoogleOAuthWrapper::loadConfig()
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

quint16 GoogleOAuthWrapper::getPort() const
{
    return m_port;
}

std::string GoogleOAuthWrapper::generateAuthorizationUrl()
{
    using namespace firebase_utils::authentication;
    auto config = m_oauthConfig.value();
    std::string authorizationUrl = config.authUri + '?';
    authorizationUrl += gGoogleOAuthScope;
    authorizationUrl += '&';
    authorizationUrl += gGoogleOAuthResponseType;
    authorizationUrl += '&';
    authorizationUrl += gGoogleOAuthState;
    authorizationUrl += '&';
    authorizationUrl +=  "redirect_uri=http://localhost:";
    authorizationUrl += std::to_string(getPort());
    authorizationUrl += '&';
    authorizationUrl += "client_id=";
    authorizationUrl += config.clientId;
    std::cout << "Authorization URL: " << authorizationUrl << std::endl;
    return authorizationUrl;
}

bool GoogleOAuthWrapper::openBrowser(const QUrl& authorizationUrl)
{
    return QDesktopServices::openUrl(authorizationUrl);
}

bool GoogleOAuthWrapper::openListenServer()
{
    m_tcpServer = new QTcpServer();
    if (m_tcpServer->listen(QHostAddress::LocalHost)) {
        m_port = m_tcpServer->serverPort();
        std::cout << "Listening on port " << m_port << " for authorization code..." << std::endl;
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
        std::cerr << "Failed to listen on port" << std::endl;
        return false;
    }

    return true;
}

bool GoogleOAuthWrapper::requestAccessToken()
{
    std::cout << "Requesting authorization code from Google..." << std::endl;
    QUrl authUrl(QString::fromStdString(generateAuthorizationUrl()));
    QUrlQuery query(authUrl);
    authUrl.setQuery(query);
    if (openBrowser(authUrl)) {
        std::cout << "Browser opened to request authorization code" << std::endl;
    } else {
        std::cerr << "Failed to open browser" << std::endl;
        return false;
    }

    return true;
}

bool GoogleOAuthWrapper::exchangeCodeForToken(const std::string& authorizationCode)
{
    std::cout << "Exchanging authorization code for access token..." << std::endl;
    auto config = m_oauthConfig.value();
    QUrl tokenUrl(QString::fromStdString(config.tokenUri));
    QNetworkRequest request(tokenUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QUrlQuery postData;
    postData.addQueryItem("code", QString::fromStdString(authorizationCode));
    postData.addQueryItem("client_id", QString::fromStdString(config.clientId));
    postData.addQueryItem("client_secret", QString::fromStdString(config.clientSecret));
    postData.addQueryItem("redirect_uri", QString::fromStdString("http://localhost:" + std::to_string(getPort())));
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
        QString accessToken = jsonObj["access_token"].toString();
        qDebug() << "Access Token: " << accessToken;
        m_googleAccessToken.accessToken = accessToken;
        m_googleAccessToken.tokenType = jsonObj["token_type"].toString();
        m_googleAccessToken.expiresIn = jsonObj["expires_in"].toString();
        m_googleAccessToken.refreshToken = jsonObj["refresh_token"].toString();
        m_googleAccessToken.scope = jsonObj["scope"].toString();
        reply->deleteLater();

        emit googleAuthenticationSuccess({
            .api = FirebaseApi::SignInWithGoogle,
            .data = m_googleAccessToken,
        });
    };
    QObject::connect(&m_networkManager, &QNetworkAccessManager::finished, replyHandler);

    return true;
}
