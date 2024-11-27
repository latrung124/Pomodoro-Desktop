/*
* FirebaseServiceImpl.cpp
* Author: Trung La
* Date: 2024-11-22
* This is an implementation class for FirebaseService
*/

#include "Implementation/Authentication/FirebaseAuthentication.h"
#include "FirebaseApp.h"
#include "FirebaseServiceImpl.h"

#include <iostream>

FirebaseServiceImpl::FirebaseServiceImpl()
    : m_isConnected(false)
{
}

FirebaseServiceImpl::~FirebaseServiceImpl()
{
}

bool FirebaseServiceImpl::connect()
{
    return true;
}

void FirebaseServiceImpl::disconnect()
{
}

bool FirebaseServiceImpl::signIn(AuthProviderType authType, const std::string &email, const std::string &password)
{
    return false;
}

bool FirebaseServiceImpl::signOut()
{
    return false;
}

bool FirebaseServiceImpl::signUp(const std::string &email, const std::string &password)
{
    return false;
}

bool FirebaseServiceImpl::deleteAccount()
{
    return false;
}

bool FirebaseServiceImpl::updatePassword(const std::string &newPassword)
{
    return false;
}
