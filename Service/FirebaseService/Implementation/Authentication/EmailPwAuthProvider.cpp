/*
* EmailPwAuthProvider.cpp
* Author: Trung La
* Date: 2024-11-24
* This is an implementation class for Email/Password authentication provider
*/

#include "Implementation/Authentication/EmailPwAuthProvider.h"

#include <QDebug>

bool EmailPwAuthProvider::signIn(const std::string &email, const std::string &password)
{
    qDebug() << "EmailPwAuthProvider::signIn() called: " << email.c_str() << " " << password.c_str();
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