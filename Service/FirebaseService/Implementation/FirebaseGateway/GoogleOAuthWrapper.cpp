/*
* OAuthWrapper.cpp
* Author: Trung La
* Date: 2024-12-10
* This is a wrapper class for OAuth authentication providers
*/

#include "FirebaseGateway/GoogleOAuthWrapper.h"

#include <QNetworkReply>
#include <QDesktopServices>
#include <QAbstractOAuth>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include <fstream>

GoogleOAuthWrapper::GoogleOAuthWrapper(QObject* parent)
    : OAuthWrapper(parent)
{
    if (loadConfig()) {
        setupOAuth2();
    } else {
        std::cerr << "Failed to load Google OAuth config" << std::endl;
    }
}

GoogleOAuthWrapper::~GoogleOAuthWrapper()
{
    delete m_oauth2;
    delete m_replyHandler;
}

void GoogleOAuthWrapper::signIn()
{
    m_oauth2->grant();
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

void GoogleOAuthWrapper::setupOAuth2()
{
    m_oauth2 = new QOAuth2AuthorizationCodeFlow(this);

    if (!m_oauthConfig.has_value()) {
        qWarning() << "No oauth config!";
        return;
    }

    auto oauthConfig = m_oauthConfig.value();

    m_oauth2->setClientIdentifier(oauthConfig.clientId.c_str());
    m_oauth2->setClientIdentifierSharedKey(oauthConfig.clientSecret.c_str());
    m_oauth2->setAuthorizationUrl(QUrl(oauthConfig.authUri.c_str()));
    m_oauth2->setAccessTokenUrl(QUrl(oauthConfig.tokenUri.c_str()));
    m_oauth2->setScope("email profile");
    m_oauth2->setContentType(QAbstractOAuth::ContentType::WwwFormUrlEncoded);

    m_replyHandler = new QOAuthHttpServerReplyHandler(8080, this);
    m_oauth2->setReplyHandler(m_replyHandler);

    connect(m_oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged,
        this, &GoogleOAuthWrapper::handleAuthStatusChanged);
    connect(m_oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
        &QDesktopServices::openUrl);
    connect(m_oauth2, &QOAuth2AuthorizationCodeFlow::granted,
        this, &GoogleOAuthWrapper::handleTokenReceived);
    connect(m_oauth2, &QOAuth2AuthorizationCodeFlow::requestFailed,
        this, &GoogleOAuthWrapper::handleRequestFailed);
}

void GoogleOAuthWrapper::handleRequestFailed(const QAbstractOAuth::Error& error)
{
    std::cerr << "Request failed: " << static_cast<int>(error) << std::endl;
}

void GoogleOAuthWrapper::handleAuthStatusChanged(const QAbstractOAuth::Status& status)
{
    switch (status) {
    case QAbstractOAuth::Status::NotAuthenticated:
        break;
    case QAbstractOAuth::Status::TemporaryCredentialsReceived:
        // Handle temporary credentials if needed
        break;
    case QAbstractOAuth::Status::Granted:
        // Already handled in granted signal
        break;
    default:
        break;
    }
}

void GoogleOAuthWrapper::handleTokenReceived()
{
    using namespace firebase_utils::API_Usage;
    m_accessToken = m_oauth2->token();
    GoogleAccessTokenResData token;
    token.accessToken = "accessToken";
    FirebaseResMsgData msgData{
        .api = FirebaseApi::SignInWithGoogle,
        .data = token,
    };
    emit googleAuthenticationSuccess(msgData);

    getUserInfo();
}

void GoogleOAuthWrapper::getUserInfo()
{
    QUrl url("https://www.googleapis.com/oauth2/v2/userinfo");
    auto reply = m_oauth2->get(url);

    connect(reply, &QNetworkReply::finished, this, [reply, this]() {
        if (reply->error() != QNetworkReply::NoError) {
            std::cerr << "Failed to get user info" << std::endl;
            return;
        }

        const auto data = reply->readAll();
        const auto jsonDoc = QJsonDocument::fromJson(data);
        const auto jsonObj = jsonDoc.object();

        if (jsonObj.contains("email")) {
            const QString email = jsonObj["email"].toString();
            std::cout << "Email: " << email.toStdString() << std::endl;
        }

        reply->deleteLater();
    });
}
