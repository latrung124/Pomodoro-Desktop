/*
* IFirebaseService.h
* Author: Trung La
* Date: 2024-11-22
* This is an interface class for FirebaseService
*/

#ifndef IFIREBASESERVICE_H
#define IFIREBASESERVICE_H

#include <string>
#include "FirebaseUtils.h"

class IFirebaseService
{
public:
    IFirebaseService() = default;
    virtual ~IFirebaseService() = default;

    IFirebaseService(const IFirebaseService&) = delete;
    IFirebaseService& operator=(const IFirebaseService&) = delete;

    virtual bool connect() = 0;
    virtual void disconnect() = 0;

    virtual bool login(AuthProviderType authType,
                        const std::string &email,
                        const std::string &password) = 0;
    virtual bool signOut() = 0;
    virtual bool createAccount(const std::string &email, const std::string &password) = 0;
    virtual bool deleteAccount() = 0;
    virtual bool updatePassword(const std::string &newPassword) = 0;
};

#endif // IFIREBASESERVICE_H
