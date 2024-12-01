/*
* FirebaseApp.cpp
* Author: Trung La
* Date: 2024-11-24
* This is the implementation of the FirebaseApp class
*/

#include "FirebaseApp.h"
#include "Authentication/FirebaseAuthentication.h"
#include "FirebaseConfig.h"

#include <QJsonDocument>
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

    m_auth = std::make_shared<FirebaseAuthentication>();
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

const std::string& FirebaseApp::getConfigJsonStr() const
{
    if (!m_isInitialized) {
        qWarning() << "FirebaseApp is not initialized";
    }

    return m_configJsonStr;
}

std::weak_ptr<FirebaseAuthentication> FirebaseApp::getAuth() const
{
    return m_auth;
}

bool FirebaseApp::parseConfigJson(ProjectConfig& config)
{
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

    config.projectInfo.projectId = projectInfoObj["project_id"].toString().toStdString();
    config.projectInfo.projectNumber = projectInfoObj["project_number"].toString().toStdString();
    config.projectInfo.storageBucket = projectInfoObj["storage_bucket"].toString().toStdString();

    QJsonObject clientObject = jsonObj["client"].toObject();
    if (clientObject.isEmpty()) {
        qWarning() << "Client info is empty";
        return false;
    }

    QJsonObject clientInfoObj = clientObject["client_info"].toObject();
    if (clientInfoObj.isEmpty()) {
        qWarning() << "Client info is empty";
        return false;
    }

    config.client.clientInfo.mobileSdkAppId = clientInfoObj["mobilesdk_app_id"].toString().toStdString();
    QJsonObject androidClientInfoObj = clientInfoObj["android_client_info"].toObject();
    if (androidClientInfoObj.isEmpty()) {
        qWarning() << "Android client info is empty";
        return false;
    }

    config.client.clientInfo.androidClientInfo.package_name = androidClientInfoObj["package_name"].toString().toStdString();

    QJsonObject oauthClientObj = clientObject["oauth_client"].toObject();
    if (oauthClientObj.isEmpty()) {
        qWarning() << "OAuth client info is empty";
        return false;
    }

    config.client.oauthClient.client_id = oauthClientObj["client_id"].toString().toStdString();
    config.client.oauthClient.client_type = oauthClientObj["client_type"].toString().toStdString();

    QJsonObject apiKeyObj = clientObject["api_key"].toObject();
    if (apiKeyObj.isEmpty()) {
        qWarning() << "API key info is empty";
        return false;
    }

    config.client.apiKey.current_key = apiKeyObj["current_key"].toString().toStdString();

    config.configVersion = jsonObj["config_version"].toString().toStdString();

    return true;
}
