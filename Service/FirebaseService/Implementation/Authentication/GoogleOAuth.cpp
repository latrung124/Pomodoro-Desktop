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

#include <iostream>
#include <fstream>
#include <string>

GoogleOAuth::GoogleOAuth()
{
    if (m_isConfigAvailable = loadConfig(); !m_isConfigAvailable) {
        std::cerr << "Failed to load Google OAuth config" << std::endl;
    }
}

std::string GoogleOAuth::requestAuthorizationCode()
{
    if (!m_isConfigAvailable) {
        std::cerr << "Google OAuth config is not available" << std::endl;
        return "";
    }

    std::cout << "Requesting authorization code from Google..." << std::endl;
    return "authorization_code";
}

std::string GoogleOAuth::exchangeCodeForToken()
{
    if (!m_isConfigAvailable) {
        std::cerr << "Google OAuth config is not available" << std::endl;
        return "";
    }

    std::cout << "Exchanging authorization code for access token..." << std::endl;
    return "access_token";
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