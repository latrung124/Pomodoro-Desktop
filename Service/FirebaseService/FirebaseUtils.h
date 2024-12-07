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
#include <variant>

#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QMetaType>

#include <QMetaType>

using namespace Qt::StringLiterals;

namespace firebase_utils {

namespace API_Usage {

const QString gFirebaseBaseUrl = "https://identitytoolkit.googleapis.com"_L1;

enum class FirebaseApi : uint16_t {
    SignInEmailPassword = 0,
    SignInWithOAuth,
    SignInAnounymous,
    SignUpEmailPassword,
    ChangePassword,
    SendPwResetEmail,
    VerifyPwResetCode,
    ConfirmPwReset,
    ChangeEmail,
    UpdateProfile,
    GetUserData,
    ExchangeCustomToken,
    ExchangeRefreshToken,
};

const QHash<FirebaseApi, QString> gFirebaseApiPath {
    {FirebaseApi::SignInEmailPassword, "/v1/accounts:signInWithPassword?key=%1"},
    {FirebaseApi::SignInAnounymous, "/v1/accounts:signUp?key=%1"},
    {FirebaseApi::SignUpEmailPassword, "/v1/accounts:signUp?key=%1"},
    {FirebaseApi::ChangePassword, "/v1/accounts:update?key=%1"},
    {FirebaseApi::SendPwResetEmail, "/v1/accounts:sendOobCode?key=%1"},
    {FirebaseApi::VerifyPwResetCode, "/v1/accounts:resetPassword?key=%1"},
    {FirebaseApi::ConfirmPwReset, "/v1/accounts:resetPassword?key=%1"},
    {FirebaseApi::ChangeEmail, "/v1/accounts:update?key=%1"},
    {FirebaseApi::UpdateProfile, "/v1/accounts:update?key=%1"},
    {FirebaseApi::GetUserData, "/v1/accounts:lookup?key=%1"},
    {FirebaseApi::ExchangeCustomToken, "/v1/accounts:signInWithCustomToken?key=%1"},
    {FirebaseApi::ExchangeRefreshToken, "/v1/token?key=%1"},
};

struct ExchangeCustomTokenResData {
    QString idToken;
    QString refreshToken;
    QString expiresIn;
};

struct ExchangeRefreshTokenResData {
    QString idToken;
    QString refreshToken;
    QString expiresIn;
    QString tokenType;
    QString userId;
    QString projectId;
};

struct SignInEmailPasswordResData {
    QString idToken;
    QString email;
    QString refreshToken;
    QString expiresIn;
    QString localId;
    bool isRegistered;
};

struct SignUpEmailPasswordResData {
    QString idToken;
    QString email;
    QString refreshToken;
    QString expiresIn;
    QString localId;
};

struct SignInAnounymousResData {
    QString idToken;
    QString refreshToken;
    QString expiresIn;
    QString localId;
};

struct ChangePasswordResData {
    QString email;
    QString localId;
    QString pwHash;
    QJsonArray providerUserInfos;
    QString idToken;
    QString refreshToken;
    QString expiresIn;
};

struct SendPwResetEmailResData {
    QString email;
    QString requestType;
};

struct VerifyPwResetCodeResData {
    QString email;
    QString requestType;
};

struct ConfirmPwResetResData {
    QString email;
    QString requestType;
};

struct ChangeEmailResData {
    QString localId;
    QString email;
    QString pwHash;
    QJsonArray providerUserInfos;
    QString idToken;
    QString refreshToken;
    QString expiresIn;
};

struct UpdateProfileResData {
    QString email;
    QString localId;
    QString displayName;
    QString photoUrl;
    QString pwHash;
    QJsonArray providerUserInfos;
    QString idToken;
    QString refreshToken;
    QString expiresIn;
};

struct GetUserDataResData {
    QString email;
    QString localId;
    bool isEmailVerified;
    QString displayName;
    QJsonArray providerUserInfos;
    QString photoUrl;
    QString pwHash;
    double passwordUpdatedAt;
    QString validSince;
    bool isDisabled;
    QString lastLoginAt;
    QString createdAt;
    QString idToken;
    bool isCustomAuth;
};

struct FirebaseResMsgData {
    FirebaseApi api;
    std::variant<ExchangeCustomTokenResData,
                 ExchangeRefreshTokenResData,
                 SignInEmailPasswordResData,
                 SignUpEmailPasswordResData,
                 SignInAnounymousResData,
                 ChangePasswordResData,
                 SendPwResetEmailResData,
                 VerifyPwResetCodeResData,
                 ConfirmPwResetResData,
                 ChangeEmailResData,
                 UpdateProfileResData,
                 GetUserDataResData> data;
};

} // namespace API_Usage


namespace config {

    struct AndroidClientInfo {
        QString package_name;
        QString certificate_hash;
    };
    struct ClientInfo {
        QString mobileSdkAppId;
        AndroidClientInfo androidClientInfo;
    };

    struct OAuthClient {
        QString client_id;
        QString client_type;
    };

    struct ApiKey {
        QString current_key;
    };

    struct ProjectInfo {
        QString projectId;
        QString projectNumber;
        QString storageBucket;
    };

    struct Client {
        ClientInfo clientInfo;
        QVector<OAuthClient> oauthClients;
        QVector<ApiKey> apiKeys;
        //Services services[];
    };

    struct ProjectConfig {
        ProjectInfo projectInfo;
        QVector<Client> clients;
        QString configVersion;
    };

} // namespace firebase_utils::config

namespace gateway {

struct FirebasePostRequest {
    QString url;
    QJsonObject payload;
};

} // namespace firebase_utils::gateway

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
using ProjectConfig = firebase_utils::config::ProjectConfig;

Q_DECLARE_METATYPE(GoogleAccessToken);
Q_DECLARE_METATYPE(firebase_utils::API_Usage::FirebaseResMsgData);

#endif // FIREBASEUTILS_H
