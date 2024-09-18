/*
 * Copyright (C) 2024 La Trung
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file is part of a desktop application based on the Qt framework.
 *
 * Author: La Trung
 */

#include "Controller/SystemController.h"
#include "Utils/CommonSettingsDefine.h"
#include "Controller/ModuleController/LoginModuleController.h"

SystemController::SystemController(QObject *parent)
    : QObject(parent)
{
    init();
}

SystemController::~SystemController()
{
    cleanup();
}

void SystemController::start()
{
    loadModule();
}

void SystemController::stop()
{
    m_engine.quit();
}

void SystemController::init()
{
    themeSetup();
}

void SystemController::cleanup()
{
}

void SystemController::setupConnections()
{
    QObject::connect(&m_engine, &QQmlApplicationEngine::quit, this, &SystemController::quit);
}

void SystemController::loadModule()
{
    // Load LoginScreen module
    using namespace Utils::SystemScreenSettings;
    m_engine.loadFromModule(moduleSettingsMap[LoginScreen].modulePath
                            , moduleSettingsMap[LoginScreen].moduleName);
}

void SystemController::themeSetup()
{
    // Create an instance of ThemeConfig
    m_themeConfig = std::make_shared<ThemeConfig>(Utils::ThemeDefine::themePath);
    // Expose ThemeConfig to QML
    m_engine.rootContext()->setContextProperty("themeConfig", m_themeConfig.get());
}

void SystemController::initModuleControllers()
{
    // Create an instance of LoginModuleController
    m_loginModuleController = std::make_unique<LoginModuleController>(m_engine.rootContext());
    m_loginModuleController->initSettings();
}