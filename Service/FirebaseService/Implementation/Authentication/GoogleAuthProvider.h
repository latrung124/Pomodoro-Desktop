/*
* GoogleAuthProvider.h
* Author: Trung La
* Date: 2024-11-24
* This is a concrete class for Google authentication provider
*/

#ifndef GOOGLEAUTHPROVIDER_H
#define GOOGLEAUTHPROVIDER_H

#include "Implementation/Authentication/AbstractExternalAuthProvider.h"
#include "FirebaseUtils.h"

#include <memory>

class GoogleOAuth;

class GoogleAuthProvider : public AbstractExternalAuthProvider
{
    Q_OBJECT
public:
    GoogleAuthProvider(firebase::auth::Auth* authApp, QObject* parent = nullptr);
    ~GoogleAuthProvider() = default;

    bool signIn() override;

public slots:
    void onGoogleAccessTokenReceived(const GoogleAccessToken& accessToken);

private:
    std::unique_ptr<GoogleOAuth> m_googleOAuth;
};

#endif // GOOGLEAUTHPROVIDER_H
