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

FirebaseAuthentication::FirebaseAuthentication(const std::shared_ptr<FirebaseGatewayManager>& gatewayManager)
    : m_gatewayManager(gatewayManager)
{
    initializeAuthProvider();
}

FirebaseAuthentication::~FirebaseAuthentication()
{
}

bool FirebaseAuthentication::isValid() const
{
    return true;
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
    m_externalAuthProviders[AuthProviderType::Google] = std::make_unique<GoogleAuthProvider>();

    // Internal Auth Providers
    m_internalAuthProviders[AuthProviderType::EmailPassword] = std::make_unique<EmailPwAuthProvider>(this);
}

std::weak_ptr<FirebaseGatewayManager> FirebaseAuthentication::getGatewayManager() const
{
    return m_gatewayManager;
}