/*
* FirebaseServiceImpl.h
* Author: Trung La
* Date: 2024-11-22
* This is an implementation class for FirebaseService
*/

#ifndef FIREBASESERVICEIMPL_H
#define FIREBASESERVICEIMPL_H

#include "IFirebaseService.h"

class FirebaseServiceImpl : public IFirebaseService
{
public:
    FirebaseServiceImpl();
    virtual ~FirebaseServiceImpl();

    bool login(AuthProviderType authType,
               const std::string &email,
               const std::string &password) override;
    bool signOut() override;
    bool createAccount(const std::string &email, const std::string &password) override;
    bool deleteAccount() override;
    bool updatePassword(const std::string &newPassword) override;
};

#endif // FIREBASESERVICEIMPL_H
