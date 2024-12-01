/*
* FirebaseApp.cpp
* Author: Trung La
* Date: 2024-11-24
* This is the implementation of the FirebaseApp class
*/

#include "FirebaseApp.h"
#include "Authentication/FirebaseAuthentication.h"

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
    qDebug() << "Config file loaded: " << m_configJsonStr.c_str();
    return !m_configJsonStr.empty();
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
