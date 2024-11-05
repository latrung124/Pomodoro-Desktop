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

#include <QObject>

class IServiceManager;

class ServiceController : public QObject
{
    Q_OBJECT

public:
    ~ServiceController();

    void start();
    void stop();

    //singleton
    static ServiceController *instance();
    std::shared_ptr<IServiceManager> serviceManager();

private:
    ServiceController(QObject *parent = nullptr);

    std::shared_ptr<IServiceManager> m_serviceManager;
};
