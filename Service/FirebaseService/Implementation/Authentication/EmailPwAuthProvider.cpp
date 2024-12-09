/*
* EmailPwAuthProvider.cpp
* Author: Trung La
* Date: 2024-11-24
* This is an implementation class for Email/Password authentication provider
*/

#include "Implementation/Authentication/EmailPwAuthProvider.h"
#include "FirebaseAuthentication.h"
#include "FirebaseGateway/FirebaseGatewayManager.h"
#include "FirebasePayloadFactory.h"

#include <QDebug>

bool EmailPwAuthProvider::signIn(const std::string &email, const std::string &password)
{
    qDebug() << "EmailPwAuthProvider::signIn() called: " << email.c_str() << " " << password.c_str();
    QJsonObject payload = FirebasePayloadFactory::createSignInPayload(email, password);
    if (auto gatewayManager = m_firebase->getGatewayManager().lock(); gatewayManager)
    {
        gatewayManager->operate(payload);
    }
    else
    {
        qWarning() << "Failed to get FirebaseGatewayManager";
    }
    return true;
}

bool EmailPwAuthProvider::signUp(const std::string &email, const std::string &password)
{
    qDebug() << "EmailPwAuthProvider::signUp() called: " << email.c_str() << " " << password.c_str();
    QJsonObject payload = FirebasePayloadFactory::createSignUpPayload(email, password);
    if (auto gatewayManager = m_firebase->getGatewayManager().lock(); gatewayManager)
    {
        gatewayManager->operate(payload);
    }
    else
    {
        qWarning() << "Failed to get FirebaseGatewayManager";
    }
    return true;
}

bool EmailPwAuthProvider::deleteAccount()
{
    return true;
}

bool EmailPwAuthProvider::updatePassword(const std::string &idToken, const std::string &newPassword)
{
    qDebug() << "EmailPwAuthProvider::updatePassword() called: " << newPassword.c_str();
    QJsonObject payload = FirebasePayloadFactory::createChangePasswordPayload(idToken, newPassword);
    if (auto gatewayManager = m_firebase->getGatewayManager().lock(); gatewayManager)
    {
        gatewayManager->operate(payload);
    }
    else
    {
        qWarning() << "Failed to get FirebaseGatewayManager";
    }
    return true;
}