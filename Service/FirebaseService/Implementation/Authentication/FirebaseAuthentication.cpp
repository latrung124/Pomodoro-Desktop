/*
* FirebaseAuthentication.cpp
* Author: Trung La
* Date: 2024-11-24
* This is an implementation class for Firebase Authentication
*/

#include "FirebaseAuthentication.h"
#include "Implementation/Authentication/GoogleAuthProvider.h"
#include "Implementation/Authentication/EmailPwAuthProvider.h"

#include <iostream>

FirebaseAuthentication::FirebaseAuthentication(firebase::App* app)
    : m_auth(firebase::auth::Auth::GetAuth(app))
{
    if (m_auth == nullptr) {
        std::cerr << "Failed to initialize Firebase Authentication" << std::endl;
        return;
    }

    initializeAuthProvider();
}

FirebaseAuthentication::~FirebaseAuthentication()
{
    if (m_auth != nullptr) {
        delete m_auth;
        m_auth = nullptr;
    }
}

bool FirebaseAuthentication::isValid() const
{
    return m_auth != nullptr;
}

bool FirebaseAuthentication::signIn(AuthProviderType authType, const std::string& email, const std::string& password)
{
    switch(authType) {
        case AuthProviderType::EmailPassword:
            return m_internalAuthProviders[AuthProviderType::EmailPassword]->signIn(email, password);
        case AuthProviderType::Google:
            return m_externalAuthProviders[AuthProviderType::Google]->signIn();
        default:
            std::cerr << "Unsupported authentication provider" << std::endl;
            return false;
    }

    return true;
}

bool FirebaseAuthentication::signUp(const std::string& email, const std::string& password)
{
    return m_internalAuthProviders[AuthProviderType::EmailPassword]->signUp(email, password);
}

bool FirebaseAuthentication::signOut()
{
    if (m_auth == nullptr) {
        std::cerr << "Firebase Authentication is not initialized" << std::endl;
        return false;
    }

    m_auth->SignOut();
    return true;
}

bool FirebaseAuthentication::deleteAccount()
{
    return m_internalAuthProviders[AuthProviderType::EmailPassword]->deleteAccount();
}

bool FirebaseAuthentication::updatePassword(const std::string& newPassword)
{
    return m_internalAuthProviders[AuthProviderType::EmailPassword]->updatePassword(newPassword);
}

void FirebaseAuthentication::initializeAuthProvider()
{
    // Initialize the authentication provider
    // External Auth Providers
    m_externalAuthProviders[AuthProviderType::Google] = std::make_unique<GoogleAuthProvider>(m_auth);

    // Internal Auth Providers
    m_internalAuthProviders[AuthProviderType::EmailPassword] = std::make_unique<EmailPwAuthProvider>(m_auth);
}