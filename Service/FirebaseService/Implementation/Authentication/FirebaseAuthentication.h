/*
* FirebaseAuthentication.h
* Author: Trung La
* Date: 2024-11-24
* This is an implementation class for Firebase Authentication
*/

#ifndef FIREBASEAUTHENTICATION_H
#define FIREBASEAUTHENTICATION_H

#include "FirebaseUtils.h"

#include <string>
#include <map>
#include <memory>

class AbstractExternalAuthProvider;
class AbstractInternalAuthProvider;

class FirebaseAuthentication
{
public:
    FirebaseAuthentication();
    virtual ~FirebaseAuthentication();

    FirebaseAuthentication(const FirebaseAuthentication&) = delete;
    FirebaseAuthentication& operator=(const FirebaseAuthentication&) = delete;
    FirebaseAuthentication(FirebaseAuthentication&&) = delete;
    FirebaseAuthentication& operator=(FirebaseAuthentication&&) = delete;

    bool isValid() const;

    bool signIn(AuthProviderType authType,
               const std::string& email = "",
               const std::string& password = "");
    bool signUp(const std::string& email, const std::string& password);
    bool signOut();
    bool deleteAccount();
    bool updatePassword(const std::string& newPassword);

private:
    void initializeAuthProvider();

    std::map<AuthProviderType, std::unique_ptr<AbstractExternalAuthProvider>> m_externalAuthProviders;
    std::map<AuthProviderType, std::unique_ptr<AbstractInternalAuthProvider>> m_internalAuthProviders;
};

#endif // FIREBASEAUTHENTICATION_H