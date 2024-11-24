/*
* FirebaseServiceImpl.cpp
* Author: Trung La
* Date: 2024-11-22
* This is an implementation class for FirebaseService
*/

#include "FirebaseServiceImpl.h"
#include "FirebaseApp.h"
#include "Implementation/Authentication/FirebaseAuthentication.h"

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
        m_firebaseAuth = std::make_unique<FirebaseAuthentication>(m_firebaseApp->getApp());
        return true;
    }

    std::cerr << "Failed to connect to Firebase" << std::endl;
    return false;
}

void FirebaseServiceImpl::disconnect()
{
    m_firebaseApp->exit();
}

bool FirebaseServiceImpl::signIn(AuthProviderType authType, const std::string &email, const std::string &password)
{
    if (!m_firebaseAuth || !m_isConnected) {
        std::cerr << "Firebase Authentication is not initialized" << std::endl;
        return false;
    }

    return m_firebaseAuth->signIn(authType, email, password);
}

bool FirebaseServiceImpl::signOut()
{
    if (!m_firebaseAuth || !m_isConnected) {
        std::cerr << "Firebase Authentication is not initialized" << std::endl;
        return false;
    }

    return m_firebaseAuth->signOut();
}

bool FirebaseServiceImpl::signUp(const std::string &email, const std::string &password)
{
    if (!m_firebaseAuth || !m_isConnected) {
        std::cerr << "Firebase Authentication is not initialized" << std::endl;
        return false;
    }

    return m_firebaseAuth->signUp(email, password);
}

bool FirebaseServiceImpl::deleteAccount()
{
    if (!m_firebaseAuth || !m_isConnected) {
        std::cerr << "Firebase Authentication is not initialized" << std::endl;
        return false;
    }

    return m_firebaseAuth->deleteAccount();
}

bool FirebaseServiceImpl::updatePassword(const std::string &newPassword)
{
    if(!m_firebaseAuth || !m_isConnected) {
        std::cerr << "Firebase Authentication is not initialized" << std::endl;
        return false;
    }

    return m_firebaseAuth->updatePassword(newPassword);
}
