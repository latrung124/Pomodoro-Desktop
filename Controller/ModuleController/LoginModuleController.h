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

#include "Controller/ModuleController/BaseModuleController.h"
#include "Utils/CloudUtility/FirebaseUtility.h"
#include "Model/Authentication/UserModel.h"

#include <memory>

class LoginModuleController : public BaseModuleController
{
    Q_OBJECT
public:
    explicit LoginModuleController(QQmlContext *context, QObject *parent = nullptr);
    ~LoginModuleController();

    void initSettings() override;
    void setupConnections() override;

    std::weak_ptr<UserModel> getUserModel() const;
    void setLoginScreen(QObject *loginScreen);

signals:
    void closeModule();

public slots:
    void open() override;
    void close() override;

    void setDisplayName(const QString &displayName);
    void setEmail(const QString &email);
    void setPassword(const QString &password);

    void onSignIn(const AuthenticationType &authType, const QString &email, const QString &password);
    void onSignUp();
    void onSignOut();

    void onResponseSignIn();
    void onResponseSignUp();

private:
    void loadModels();

    std::shared_ptr<UserModel> m_userModel;
    QObject *m_loginScreen = nullptr;
};
