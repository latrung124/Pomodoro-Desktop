/*
* EmailPwAuthProvider.cpp
* Author: Trung La
* Date: 2024-11-24
* This is an implementation class for Email/Password authentication provider
*/

#include "Implementation/Authentication/EmailPwAuthProvider.h"

#include <iostream>

EmailPwAuthProvider::EmailPwAuthProvider(firebase::auth::Auth* authApp)
    : AbstractInternalAuthProvider(authApp)
{
}

bool EmailPwAuthProvider::signIn(const std::string &email, const std::string &password)
{
    if (m_auth == nullptr) {
        std::cerr << "Firebase Authentication is not initialized" << std::endl;
        return false;
    }

    firebase::Future<firebase::auth::AuthResult> result =
        m_auth->SignInWithEmailAndPassword(email.c_str(), password.c_str());

    result.OnCompletion([](const firebase::Future<firebase::auth::AuthResult>& resultData, void* userData) {
        if (resultData.error() == firebase::auth::kAuthErrorNone) {
            std::cerr << "Sign in successful" << std::endl;
        } else {
            std::cerr << "Sign in failed" << std::endl;
        }
    }, nullptr);

    return true;
}

bool EmailPwAuthProvider::signUp(const std::string &email, const std::string &password)
{
    if (m_auth == nullptr) {
        std::cerr << "Firebase Authentication is not initialized" << std::endl;
        return false;
    }

    firebase::Future<firebase::auth::AuthResult> result =
        m_auth->CreateUserWithEmailAndPassword(email.c_str(), password.c_str());

    while (result.status() == firebase::kFutureStatusPending) {
        // Wait until the operation is complete
        std::cout << "Signing up..." << std::endl;
    }

    result.OnCompletion([](const firebase::Future<firebase::auth::AuthResult>& resultData, void* userData) {
        if (resultData.error() == firebase::auth::kAuthErrorNone) {
            std::cerr << "Account created successfully" << std::endl;
        } else {
            std::cerr << "Failed to create account" << std::endl;
        }
    }, nullptr);

    return true;
}

bool EmailPwAuthProvider::deleteAccount()
{
    if (m_auth == nullptr) {
        std::cerr << "Firebase Authentication is not initialized" << std::endl;
        return false;
    }

    auto user = m_auth->current_user();
    if (!user.is_valid()) {
        std::cerr << "No user is currently signed in" << std::endl;
        return false;
    }

    auto result = user.Delete();
    result.OnCompletion([](const firebase::Future<void>& resultData, void* userData) {
        if (resultData.error() == firebase::auth::kAuthErrorNone) {
            std::cerr << "Account deleted successfully" << std::endl;
        } else {
            std::cerr << "Failed to delete account" << std::endl;
        }
    }, nullptr);

    return true;
}

bool EmailPwAuthProvider::updatePassword(const std::string &newPassword)
{
    if (m_auth == nullptr) {
        std::cerr << "Firebase Authentication is not initialized" << std::endl;
        return false;
    }

    auto user = m_auth->current_user();
    if (!user.is_valid()) {
        std::cerr << "No user is currently signed in" << std::endl;
        return false;
    }

    auto result = user.UpdatePassword(newPassword.c_str());
    result.OnCompletion([](const firebase::Future<void>& resultData, void* userData) {
        if (resultData.error() == firebase::auth::kAuthErrorNone) {
            std::cerr << "Password updated successfully" << std::endl;
        } else {
            std::cerr << "Failed to update password" << std::endl;
        }
    }, nullptr);

    return true;
}