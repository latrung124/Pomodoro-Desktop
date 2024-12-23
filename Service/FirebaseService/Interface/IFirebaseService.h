/*
* IFirebaseService.h
* Author: Trung La
* Date: 2024-11-22
* This is an interface class for FirebaseService
*/

#ifndef IFIREBASESERVICE_H
#define IFIREBASESERVICE_H

#include "IBaseService.h"
#include "FirebaseUtils.h"

#include <string>

class IFirebaseService : public IBaseService
{
public:
    IFirebaseService() = default;
    virtual ~IFirebaseService() = default;

    IFirebaseService(const IFirebaseService&) = delete;
    IFirebaseService& operator=(const IFirebaseService&) = delete;

    virtual bool signIn(AuthProviderType authType,
                        const std::string &email = "",
                        const std::string &password = "") = 0;
    virtual bool signOut() = 0;
    virtual bool signUp(const std::string &email, const std::string &password) = 0;
    virtual bool deleteAccount() = 0;
    virtual bool updatePassword(const std::string &idToken, const std::string &newPassword) = 0;
};

#endif // IFIREBASESERVICE_H
