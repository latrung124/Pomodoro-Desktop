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

class QQmlContext;

class BaseModuleController : public QObject
{
    Q_OBJECT
public:
    BaseModuleController(QQmlContext *context, QObject *parent = nullptr) : m_context(context) {};
    virtual ~BaseModuleController() {};

    virtual void open() = 0;
    virtual void close() = 0;

protected:
    virtual void initSettings() = 0;
    QQmlContext *m_context;
};
