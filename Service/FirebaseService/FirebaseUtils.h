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

namespace firebase_utils {

namespace authentication {

enum class AuthProviderType : uint16_t {
    None,
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

} // namespace firebase_utils::authentication

} // namespace firebase_utils

using AuthProviderType = firebase_utils::authentication::AuthProviderType;

#endif // FIREBASEUTILS_H
