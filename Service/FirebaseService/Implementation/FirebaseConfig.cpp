/*
* FirebaseConfig.cpp
* Author: Trung La
* Date: 2024-12-01
* This class is a helper class for FirebaseConfig
*/

#include "FirebaseConfig.h"

void FirebaseConfig::setProjectConfig(const ProjectConfig &config)
{
    m_projectConfig = config;
}

std::optional<ProjectConfig> FirebaseConfig::getProjectConfig() const
{
    return m_projectConfig;
}

void FirebaseConfig::setOAuthConfig(const OAuthConfig &config)
{
    m_oauthConfig = config;
}

OAuthConfig FirebaseConfig::getOAuthConfig() const
{
    return m_oauthConfig;
}
