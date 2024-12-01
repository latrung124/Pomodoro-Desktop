/*
* EmailPwAuthProvider.cpp
* Author: Trung La
* Date: 2024-11-24
* This is an implementation class for Email/Password authentication provider
*/

#include "Implementation/Authentication/EmailPwAuthProvider.h"
#include "Helper/FirebaseGatewayHelper.h"
#include "Helper/FirebaseFactoryHelper.h"
#include "Helper/FirebaseConfigHelper.h"

#include <QDebug>

bool EmailPwAuthProvider::signIn(const std::string &email, const std::string &password)
{
    qDebug() << "EmailPwAuthProvider::signIn() called: " << email.c_str() << " " << password.c_str();

    auto request = firebase_helper::factory::constructSignInRequest(email, password);
    request.url += firebase_helper::config::getCurrentApiKey();
    firebase_helper::gateway::postRequest(request);

    return true;
}

bool EmailPwAuthProvider::signUp(const std::string &email, const std::string &password)
{
    return true;
}

bool EmailPwAuthProvider::deleteAccount()
{
    return true;
}

bool EmailPwAuthProvider::updatePassword(const std::string &newPassword)
{
    return true;
}