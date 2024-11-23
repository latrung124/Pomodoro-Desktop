/*
* FirebaseServiceImpl.cpp
* Author: Trung La
* Date: 2024-11-22
* This is an implementation class for FirebaseService
*/

#include "FirebaseServiceImpl.h"
#include "FirebaseApp.h"

#include <iostream>

FirebaseServiceImpl::FirebaseServiceImpl()
    : m_isConnected(false)
    , m_firebaseApp(std::make_unique<FirebaseApp>())
{
}

FirebaseServiceImpl::~FirebaseServiceImpl()
{
}

bool FirebaseServiceImpl::connect()
{
    if (m_isConnected = m_firebaseApp->initialize(); m_isConnected) {
        // Connect to Firebase
        std::cout << "Connected to Firebase" << std::endl;
        return true;
    }

    std::cerr << "Failed to connect to Firebase" << std::endl;
    return false;
}

void FirebaseServiceImpl::disconnect()
{
    m_firebaseApp->exit();
}

bool FirebaseServiceImpl::login(AuthProviderType authType, const std::string &email, const std::string &password)
{
    // Implementation of login method
    return true;
}

bool FirebaseServiceImpl::signOut()
{
    // Implementation of signOut method
    return true;
}

bool FirebaseServiceImpl::createAccount(const std::string &email, const std::string &password)
{
    // Implementation of createAccount method
    return true;
}

bool FirebaseServiceImpl::deleteAccount()
{
    // Implementation of deleteAccount method
    return true;
}

bool FirebaseServiceImpl::updatePassword(const std::string &newPassword)
{
    // Implementation of updatePassword method
    return true;
}
