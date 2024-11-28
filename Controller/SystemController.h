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

#pragma once

#include "ThemeConfig/ThemeConfig.h"
#include "BaseController.h"

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QResource>

#include <memory>

class LoginModuleController;
class SystemController : public BaseController
{
    Q_OBJECT
public:
    SystemController(QObject *parent = nullptr);
    ~SystemController();

public slots:
    void start();
    void stop();

signals:
    void quit();

private:
    void init();
    void cleanup();
    void setupConnections();

    void themeSetup();
    void loadModule();
    void initModuleControllers();

    QQmlApplicationEngine m_engine;
    std::shared_ptr<ThemeConfig> m_themeConfig;
    std::unique_ptr<LoginModuleController> m_loginModuleController;
};
