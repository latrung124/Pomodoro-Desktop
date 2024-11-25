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
    // m_firebaseApp = new FirebaseApp();

    // if (m_isConnected = m_firebaseApp->initialize(); m_isConnected) {
    //     // Connect to Firebase
    //     std::cout << "Connected to Firebase" << std::endl;
    //     m_firebaseAuth = new FirebaseAuthentication(m_firebaseApp->getApp());
    //     return true;
    // }

    // std::cerr << "Failed to connect to Firebase" << std::endl;
    return false;
}

void FirebaseServiceImpl::disconnect()
{
    // m_firebaseApp->exit();
    // if (m_firebaseApp) {
    //     delete m_firebaseApp;
    //     m_firebaseApp = nullptr;
    // }
    // if (m_firebaseAuth) {
    //     delete m_firebaseAuth;
    //     m_firebaseAuth = nullptr;
    // }
}

bool FirebaseServiceImpl::signIn(AuthProviderType authType, const std::string &email, const std::string &password)
{
    // if (!m_firebaseAuth || !m_isConnected) {
    //     std::cerr << "Firebase Authentication is not initialized" << std::endl;
    //     return false;
    // }

    // return m_firebaseAuth->signIn(authType, email, password);
    return false;
}

bool FirebaseServiceImpl::signOut()
{
    // if (!m_firebaseAuth || !m_isConnected) {
    //     std::cerr << "Firebase Authentication is not initialized" << std::endl;
    //     return false;
    // }

    // return m_firebaseAuth->signOut();
    return false;
}

bool FirebaseServiceImpl::signUp(const std::string &email, const std::string &password)
{
    // if (!m_firebaseAuth || !m_isConnected) {
    //     std::cerr << "Firebase Authentication is not initialized" << std::endl;
    //     return false;
    // }

    // return m_firebaseAuth->signUp(email, password);
    return false;
}

bool FirebaseServiceImpl::deleteAccount()
{
    // if (!m_firebaseAuth || !m_isConnected) {
    //     std::cerr << "Firebase Authentication is not initialized" << std::endl;
    //     return false;
    // }

    // return m_firebaseAuth->deleteAccount();
    return false;
}

bool FirebaseServiceImpl::updatePassword(const std::string &newPassword)
{
    // if(!m_firebaseAuth || !m_isConnected) {
    //     std::cerr << "Firebase Authentication is not initialized" << std::endl;
    //     return false;
    // }

    // return m_firebaseAuth->updatePassword(newPassword);
    return false;
}
