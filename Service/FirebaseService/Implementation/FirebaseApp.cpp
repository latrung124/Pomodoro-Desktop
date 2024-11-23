/*
* FirebaseApp.cpp
* Author: Trung La
* Date: 2024-11-24
* This is the implementation of the FirebaseApp class
*/

#include "FirebaseApp.h"

#include <string>
#include <fstream>
#include <iostream>

FirebaseApp::FirebaseApp()
    : m_app(nullptr)
    , m_options(nullptr)
{
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
        std::cerr << "Failed to open config file: " << configPath << std::endl;
        return false;
    }

    std::string configJson = std::string((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());
    m_options = firebase::AppOptions::LoadFromJsonConfig(configJson.c_str());
    if (m_options == nullptr) {
        std::cerr << "Failed to load app options from config file" << std::endl;
        return false;
    }

    m_app = firebase::App::Create(*m_options);

    return m_app != nullptr;
}

void FirebaseApp::exit()
{
    if (m_app != nullptr) {
        delete m_app;
        m_app = nullptr;
    }

    if (m_options != nullptr) {
        delete m_options;
        m_options = nullptr;
    }
}

firebase::App* FirebaseApp::getApp()
{
    return m_app;
}