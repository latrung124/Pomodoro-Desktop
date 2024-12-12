/*
* FirebaseConfig.h
* Author: Trung La
* Date: 2024-12-01
* This class is a helper class for FirebaseConfig
*/

#ifndef FIREBASECONFIG_H
#define FIREBASECONFIG_H

#include "FirebaseUtils.h"

#include <optional>

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
    std::optional<ProjectConfig> getProjectConfig() const;

    void setOAuthConfig(const OAuthConfig &config);
    OAuthConfig getOAuthConfig() const;

private:
    FirebaseConfig() = default;

    std::optional<ProjectConfig> m_projectConfig;
    OAuthConfig m_oauthConfig;
};

#endif // FIREBASECONFIG_H
