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

#include "Controller/ModuleController/LoginModuleController.h"
#include "Core/Helper/Firebase/FirebaseRequestHelper.h"
#include "Core/Helper/ControllerHelper.h"
#include "Controller/SystemController.h"

#include <QQmlContext>
#include <QDebug>

LoginModuleController::LoginModuleController(QQmlContext *context, QObject *parent)
    : BaseModuleController(context, parent)
{
    if (context) {
        context->setContextProperty("loginModuleController", this);
    }
}

LoginModuleController::~LoginModuleController()
{
}

void LoginModuleController::open()
{
}

void LoginModuleController::close()
{
    emit closeModule();
}

void LoginModuleController::initSettings()
{
    m_userModel = std::make_shared<UserModel>();
}

void LoginModuleController::setupConnections()
{
    auto systemController = helper::system::getController<SystemController>();
    connect(this, &LoginModuleController::closeModule, systemController.get(), &SystemController::stop);
}

void LoginModuleController::setLoginScreen(QObject *loginScreen)
{
    if (!loginScreen) {
        return;
    }
    m_loginScreen = loginScreen;

    loadModels();
}

std::weak_ptr<UserModel> LoginModuleController::getUserModel() const
{
    return m_userModel;
}

void LoginModuleController::loadModels()
{
    if (!m_userModel) {
        return;
    }

    m_loginScreen->setProperty("userModel", QVariant::fromValue(m_userModel.get()));
}

void LoginModuleController::setDisplayName(const QString &displayName)
{
    if (!m_userModel) {
        return;
    }

    m_userModel->setDisplayName(displayName);
}

void LoginModuleController::setEmail(const QString &email)
{
    if (!m_userModel) {
        return;
    }

    m_userModel->setEmail(email);
}

void LoginModuleController::setPassword(const QString &password)
{
    if (!m_userModel) {
        return;
    }

    m_userModel->setPassword(password);
}

void LoginModuleController::onSignIn(const AuthenticationType &authType
                                    , const QString &email, const QString &password)
{
    qDebug() << "Sign in request for user" << email;
    m_userModel->setAuthenticationType(authType);
    m_userModel->setEmail(email);
    helper::firebase::constructSignInRequest(authType, email.toStdString(), password.toStdString());
}

void LoginModuleController::onSignUp()
{
    qDebug() << "Sign up request for user";
    helper::firebase::constructSignUpRequest(m_userModel->email().toStdString(), m_userModel->password().toStdString());
}

void LoginModuleController::onSignOut()
{
    qDebug() << "Sign out request";
}

void LoginModuleController::onResponseSignIn()
{
    if (m_loginScreen) {
        QMetaObject::invokeMethod(m_loginScreen, "onResponseSignIn");
    } else {
        qDebug() << "LoginModuleController:: onResponseSignIn: loginScreen is null";
    }
}

void LoginModuleController::onResponseSignUp()
{
    if (m_loginScreen) {
        QMetaObject::invokeMethod(m_loginScreen, "onResponseSignUp");
    } else {
        qDebug() << "LoginModuleController:: onResponseSignUp: loginScreen is null";
    }
}
