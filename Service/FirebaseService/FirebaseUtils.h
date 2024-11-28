/*
* FirebaseUtils.h
* Author: Trung La
* Date: 2024-11-22
* This is a utility class for FirebaseService
*/

#ifndef FIREBASEUTILS_H
#define FIREBASEUTILS_H

#include <cstdint>
#include <string>

#include <QMetaType>

namespace firebase_utils {

namespace authentication {

enum class AuthProviderType : uint16_t {
    None = 0,
    EmailPassword,
    Google,
    Facebook,
    Twitter,
    GitHub,
    Anonymous,
    Phone,
    Custom,
    PlayGames,
    Apple,
    GameCenter,
    Steam,
    Microsoft,
    Yahoo,
    Huawei,
    WeChat,
    Last,
};

struct OAuthConfig {
    std::string clientId;
    std::string projectId;
    std::string clientSecret;
    std::string redirectUri;
    std::string authUri;
    std::string tokenUri;
    std::string platform;
};

struct GoogleAccessToken {
    std::string accessToken;
    std::string tokenType;
    std::string expiresIn;
    std::string refreshToken;
    std::string scope;
};

const std::string gGoogleOAuthScope = "scope=email%20profile";
const std::string gGoogleOAuthResponseType = "response_type=code";
const std::string gGoogleOAuthState = "state=security_token%3D138r5719ru3e1%26url%3Dhttps%3A%2F%2Foauth2.example.com%2Ftoken";

} // namespace firebase_utils::authentication

} // namespace firebase_utils

using AuthProviderType = firebase_utils::authentication::AuthProviderType;
using OAuthConfig = firebase_utils::authentication::OAuthConfig;
using GoogleAccessToken = firebase_utils::authentication::GoogleAccessToken;

Q_DECLARE_METATYPE(GoogleAccessToken);

#endif // FIREBASEUTILS_H
