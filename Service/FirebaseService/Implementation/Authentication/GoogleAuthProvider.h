/*
* GoogleAuthProvider.h
* Author: Trung La
* Date: 2024-11-24
* This is a concrete class for Google authentication provider
*/

#ifndef GOOGLEAUTHPROVIDER_H
#define GOOGLEAUTHPROVIDER_H

#include "Implementation/Authentication/AbstractExternalAuthProvider.h"

#include <memory>

class GoogleOAuth;

class GoogleAuthProvider : public AbstractExternalAuthProvider
{
public:
    GoogleAuthProvider(firebase::auth::Auth* authApp);
    ~GoogleAuthProvider() = default;

    bool signIn() override;

private:
    std::unique_ptr<GoogleOAuth> m_googleOAuth;
};

#endif // GOOGLEAUTHPROVIDER_H