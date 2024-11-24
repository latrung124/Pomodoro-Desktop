/*
* GoogleAuthProvider.cpp
* Author: Trung La
* Date: 2024-11-24
* This is a concrete class for Google authentication provider
*/

#include "GoogleAuthProvider.h"
#include "Implementation/Authentication/GoogleOAuth.h"

GoogleAuthProvider::GoogleAuthProvider(firebase::auth::Auth* authApp)
    : AbstractExternalAuthProvider(authApp)
    , m_googleOAuth(std::make_unique<GoogleOAuth>())
{
}

bool GoogleAuthProvider::signIn()
{
    // Sign in with Google
    return true;
}