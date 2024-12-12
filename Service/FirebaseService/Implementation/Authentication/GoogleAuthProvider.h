/*
* GoogleAuthProvider.h
* Author: Trung La
* Date: 2024-11-24
* This is a concrete class for Google authentication provider
*/

#ifndef GOOGLEAUTHPROVIDER_H
#define GOOGLEAUTHPROVIDER_H

#include "Implementation/Authentication/AbstractExternalAuthProvider.h"

class GoogleAuthProvider : public AbstractExternalAuthProvider
{
public:
    GoogleAuthProvider(const FirebaseAuthentication *firebaseAuth)
     : AbstractExternalAuthProvider(firebaseAuth) {}
    ~GoogleAuthProvider() = default;

    bool signIn() override;
};

#endif // GOOGLEAUTHPROVIDER_H
