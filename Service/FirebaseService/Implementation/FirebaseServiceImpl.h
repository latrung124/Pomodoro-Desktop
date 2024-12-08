/*
* FirebaseServiceImpl.h
* Author: Trung La
* Date: 2024-11-22
* This is an implementation class for FirebaseService
*/

#ifndef FIREBASESERVICEIMPL_H
#define FIREBASESERVICEIMPL_H

#include "IFirebaseService.h"

#include <memory>

class FirebaseApp;

class FirebaseServiceImpl : public IFirebaseService
{
public:
    FirebaseServiceImpl();
    virtual ~FirebaseServiceImpl();

    bool connect() override;
    void disconnect() override;

    void registerListener(IBaseServiceListenerPtr listener) override;
    void unregisterListener(IBaseServiceListenerPtr listener) override;

    bool signIn(AuthProviderType authType,
               const std::string &email = "",
               const std::string &password = "") override;
    bool signOut() override;
    bool signUp(const std::string &email, const std::string &password) override;
    bool deleteAccount() override;
    bool updatePassword(const std::string &newPassword) override;

private:
    bool m_isConnected;
    std::unique_ptr<FirebaseApp> m_firebaseApp;
};

#endif // FIREBASESERVICEIMPL_H
