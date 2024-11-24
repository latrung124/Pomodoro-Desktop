/*
* AbstractInternalAuthProvider.h
* Author: Trung La
* Date: 2024-11-24
* This is an abstract class for internal authentication providers
*/

#ifndef ABSTRACTINTERNALAUTHPROVIDER_H
#define ABSTRACTINTERNALAUTHPROVIDER_H

#include <firebase/auth.h>

#include <string>

class AbstractInternalAuthProvider
{
public:
    AbstractInternalAuthProvider(firebase::auth::Auth* authApp) :m_auth(authApp) {}
    virtual ~AbstractInternalAuthProvider() = default;

    AbstractInternalAuthProvider(const AbstractInternalAuthProvider&) = delete;
    AbstractInternalAuthProvider& operator=(const AbstractInternalAuthProvider&) = delete;
    AbstractInternalAuthProvider(AbstractInternalAuthProvider&&) = delete;
    AbstractInternalAuthProvider& operator=(AbstractInternalAuthProvider&&) = delete;

    virtual bool signIn(const std::string &email, const std::string &password) = 0;
    virtual bool deleteAccount() = 0;
    virtual bool signUp(const std::string &email, const std::string &password) = 0;
    virtual bool updatePassword(const std::string &newPassword) = 0;

protected:
    firebase::auth::Auth* m_auth;
};

#endif // ABSTRACTINTERNALAUTHPROVIDER_H