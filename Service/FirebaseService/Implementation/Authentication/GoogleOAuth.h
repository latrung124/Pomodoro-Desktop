/*
* GoogleOAuth.h
* Author: Trung La
* Date: 2024-11-24
* This is an implementation class for Google OAuth authentication provider
*/

#ifndef GOOGLEOAUTH_H
#define GOOGLEOAUTH_H

#include "FirebaseUtils.h"

#include <string>

class GoogleOAuth {
public:
    GoogleOAuth();
    ~GoogleOAuth() = default;

    std::string requestAuthorizationCode();
    std::string exchangeCodeForToken();

private:
    bool loadConfig();
    std::string generateAuthorizationUrl();

    OAuthConfig m_oauthConfig;
    bool m_isConfigAvailable;
};

#endif // GOOGLEOAUTH_H