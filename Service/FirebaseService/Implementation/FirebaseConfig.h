/*
* FirebaseConfig.h
* Author: Trung La
* Date: 2024-12-01
* This class is a helper class for FirebaseConfig
*/

#ifndef FIREBASECONFIG_H
#define FIREBASECONFIG_H

#include "FirebaseUtils.h"

class FirebaseConfig
{
public:
    static FirebaseConfig& instance()
    {
        static FirebaseConfig instance;
        return instance;
    }
    ~FirebaseConfig() = default;

    void setProjectConfig(const ProjectConfig &config);
    ProjectConfig getProjectConfig() const;

    void setOAuthConfig(const OAuthConfig &config);
    OAuthConfig getOAuthConfig() const;

    void setGoogleAccessToken(const GoogleAccessToken &token);
    GoogleAccessToken getGoogleAccessToken() const;

private:
    FirebaseConfig() = default;

    ProjectConfig m_projectConfig;
    OAuthConfig m_oauthConfig;
    GoogleAccessToken m_googleAccessToken;
};

#endif // FIREBASECONFIG_H