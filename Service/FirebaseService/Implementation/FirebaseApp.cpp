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
}

void FirebaseApp::exit()
{
}