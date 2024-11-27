/*
* GoogleAuthProvider.cpp
* Author: Trung La
* Date: 2024-11-24
* This is a concrete class for Google authentication provider
*/

#include "GoogleAuthProvider.h"
#include "Implementation/Authentication/GoogleOAuth.h"

GoogleAuthProvider::GoogleAuthProvider(QObject *parent)
    : AbstractExternalAuthProvider(parent)
    , m_googleOAuth(std::make_unique<GoogleOAuth>())
{
    QObject::connect(m_googleOAuth.get(), &GoogleOAuth::googleAccessTokenReceived,
                    this, &GoogleAuthProvider::onGoogleAccessTokenReceived);
}

bool GoogleAuthProvider::signIn()
{
    if (m_googleOAuth->requestAccessToken()) {
        return true;
    }
    return true;
}

void GoogleAuthProvider::onGoogleAccessTokenReceived(const GoogleAccessToken& accessToken)
{
    // Exchange the access token for a Firebase credential
}
