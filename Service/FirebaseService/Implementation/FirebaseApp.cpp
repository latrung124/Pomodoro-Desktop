/*
* FirebaseApp.cpp
* Author: Trung La
* Date: 2024-11-24
* This is the implementation of the FirebaseApp class
*/

#include "FirebaseApp.h"
#include "Authentication/FirebaseAuthentication.h"
#include "FirebaseListenerManager.h"
#include "FirebaseGateway/FirebaseGatewayManager.h"
#include "FirebaseConfig.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>

#include <string>
#include <fstream>

FirebaseApp::FirebaseApp()
    : m_isInitialized(false)
    , m_configJsonStr("")
{
    m_isInitialized = initialize();
    if (!m_isInitialized) {
        qWarning() << "Failed to initialize FirebaseApp";
        return;
    }

    FirebaseConfig::instance().setProjectConfig(m_projectConfig);

    m_gatewayManager = std::make_shared<FirebaseGatewayManager>();
    m_gatewayManager->init();
    m_listenerManager = std::make_shared<FirebaseListenerManager>();
    m_gatewayManager->setFirebaseListenerManager(m_listenerManager);
    m_auth = std::make_shared<FirebaseAuthentication>(m_gatewayManager);
}

FirebaseApp::~FirebaseApp()
{
    exit();
}

bool FirebaseApp::initialize()
{
    std::string configPath = std::string(FIREBASE_CONFIG_PATH) + "/google-services.json";

    std::ifstream configFile(configPath);
    if(!configFile.is_open()) {
        qWarning() << "Failed to open config file: " << configPath;
        return false;
    }

    m_configJsonStr = std::string((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());
    configFile.close();
    if (m_configJsonStr.empty()) {
        qWarning() << "Config file is empty";
        return false;
    }

    return parseConfigJson(m_projectConfig);
}

void FirebaseApp::exit()
{
}

bool FirebaseApp::isInitialized() const
{
    return m_isInitialized;
}

std::weak_ptr<FirebaseAuthentication> FirebaseApp::getAuth() const
{
    return m_auth;
}

std::weak_ptr<FirebaseListenerManager> FirebaseApp::getListenerManager() const
{
    return m_listenerManager;
}

bool FirebaseApp::parseConfigJson(ProjectConfig& config)
{
    using namespace firebase_utils::config;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QString::fromStdString(m_configJsonStr).toUtf8());
    if (jsonDoc.isNull()) {
        qWarning() << "Failed to parse config json";
        return false;
    }

    QJsonObject jsonObj = jsonDoc.object();
    if (jsonObj.isEmpty()) {
        qWarning() << "Config json is empty";
        return false;
    }

    QJsonObject projectInfoObj = jsonObj["project_info"].toObject();
    if (projectInfoObj.isEmpty()) {
        qWarning() << "Project info is empty";
        return false;
    }

    config.projectInfo.projectId = projectInfoObj["project_id"].toString();
    config.projectInfo.projectNumber = projectInfoObj["project_number"].toString();
    config.projectInfo.storageBucket = projectInfoObj["storage_bucket"].toString();

    QJsonArray clientArray = jsonObj["client"].toArray();
    if (clientArray.isEmpty()) {
        qWarning() << "Client array is empty";
        return false;
    }

    for (const auto& client : clientArray) {
        QJsonObject clientObject = client.toObject();
        if (clientObject.isEmpty()) {
            qWarning() << "Client info is empty";
            return false;
        }

        QJsonObject clientInfoObj = clientObject["client_info"].toObject();
        if (clientInfoObj.isEmpty()) {
            qWarning() << "Client info is empty";
            return false;
        }

        Client client;

        client.clientInfo.mobileSdkAppId = clientInfoObj["mobilesdk_app_id"].toString();
        QJsonObject androidClientInfoObj = clientInfoObj["android_client_info"].toObject();
        if (androidClientInfoObj.isEmpty()) {
            qWarning() << "Android client info is empty";
            return false;
        }

        client.clientInfo.androidClientInfo.package_name = androidClientInfoObj["package_name"].toString();

        QJsonArray oauthClientArray = clientObject["oauth_client"].toArray();
        if (oauthClientArray.isEmpty()) {
            qWarning() << "OAuth client array is empty";
            return false;
        }

        for (const auto& oauthClient : oauthClientArray) {
            QJsonObject oauthClientObj = oauthClient.toObject();
            if (oauthClientObj.isEmpty()) {
                qWarning() << "OAuth client info is empty";
                return false;
            }

            OAuthClient oauthClient;
            oauthClient.client_id = oauthClientObj["client_id"].toString();
            oauthClient.client_type = oauthClientObj["client_type"].toString();
            client.oauthClients.emplace_back(oauthClient);
        }

        QJsonArray apiKeyArray = clientObject["api_key"].toArray();
        if (apiKeyArray.isEmpty()) {
            qWarning() << "API key array is empty";
            return false;
        }

        for (const auto& apiKey : apiKeyArray) {
            QJsonObject apiKeyObj = apiKey.toObject();
            if (apiKeyObj.isEmpty()) {
                qWarning() << "API key info is empty";
                return false;
            }

            ApiKey apiKey;
            apiKey.current_key = apiKeyObj["current_key"].toString();
            client.apiKeys.emplace_back(apiKey);
        }

        config.clients.emplace_back(client);
    }

    config.configVersion = jsonObj["config_version"].toString();

    return true;
}
