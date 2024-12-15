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
    : BaseController(parent)
    , m_engine(new QQmlApplicationEngine(this))
{
    init();
    setupConnections();
}

SystemController::~SystemController()
{
    cleanup();
}

void SystemController::start()
{
    loadModules();
    loadModels();
    setupConnections();
}

void SystemController::stop()
{
    cleanup();
}

void SystemController::init()
{
    themeSetup();
    initModuleControllers();
}

void SystemController::cleanup()
{
    m_loginModuleController->deleteLater();
    m_themeConfig->deleteLater();
    m_engine->deleteLater();
}

void SystemController::setupConnections()
{
    if (!m_loginModuleController) {
        return;
    }
    m_loginModuleController->setupConnections();
}

void SystemController::loadModules()
{
    // Load LoginScreen module
    using namespace Utils::SystemScreenSettings;
    m_engine->loadFromModule(moduleSettingsMap[LoginScreen].modulePath
                            , moduleSettingsMap[LoginScreen].moduleName);
}

void SystemController::themeSetup()
{
    // Create an instance of ThemeConfig
    m_themeConfig = std::make_shared<ThemeConfig>();
    // Expose ThemeConfig to QML
    m_engine->rootContext()->setContextProperty("themeConfig", m_themeConfig.get());
}

void SystemController::initModuleControllers()
{
    // Create an instance of LoginModuleController
    m_loginModuleController = std::make_shared<LoginModuleController>(m_engine->rootContext());
    m_loginModuleController->initSettings();
}

void SystemController::loadModels()
{
    auto objList = m_engine->rootObjects();
    for (auto obj : objList) {
        if (obj->objectName() == "loginScreen") {
            auto loginScreen = obj->findChild<QObject*>("loginScreen");
            loadLoginModels(loginScreen);
        }
    }
}

void SystemController::loadLoginModels(QObject *loginScreen)
{
    if (!loginScreen) {
        return;
    }

    auto userModel = m_loginModuleController->getUserModel().lock();
    if (!userModel) {
        return;
    }

    loginScreen->setProperty("userModel", QVariant::fromValue(userModel.get()));
}

std::weak_ptr<LoginModuleController> SystemController::getLoginModuleController() const
{
    return m_loginModuleController;
}
