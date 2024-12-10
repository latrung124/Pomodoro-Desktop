/*
* FirebasePayloadFactory.cpp
* Author: Trung La
* Date: 2024-12-05
* This is the implementation of the FirebasePayloadFactory class
*/

#include "FirebasePayloadFactory.h"

QJsonObject FirebasePayloadFactory::createSignInPayload(const std::string &email, const std::string &password)
{
    QJsonObject payload;
    payload["apiId"] = static_cast<int>(FirebaseApi::SignInEmailPassword);
    payload["email"] = email.c_str();
    payload["password"] = password.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createSignUpPayload(const std::string &email, const std::string &password)
{
    QJsonObject payload;
    payload["apiId"] = static_cast<int>(FirebaseApi::SignUpEmailPassword);
    payload["email"] = email.c_str();
    payload["password"] = password.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createChangePasswordPayload(const std::string &idToken, const std::string &password)
{
    QJsonObject payload;
    payload["apiId"] = static_cast<int>(FirebaseApi::ChangePassword);
    payload["idToken"] = idToken.c_str();
    payload["password"] = password.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createSendPwResetEmailPayload(const std::string &email)
{
    QJsonObject payload;
    payload["apiId"] = static_cast<int>(FirebaseApi::SendPwResetEmail);
    payload["email"] = email.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createVerifyPwResetCodePayload(const std::string &email, const std::string &code)
{
    QJsonObject payload;
    payload["apiId"] = static_cast<int>(FirebaseApi::VerifyPwResetCode);
    payload["email"] = email.c_str();
    payload["code"] = code.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createConfirmPwResetPayload(const std::string &email, const std::string &code, const std::string &newPassword)
{
    QJsonObject payload;
    payload["apiId"] = static_cast<int>(FirebaseApi::ConfirmPwReset);
    payload["email"] = email.c_str();
    payload["code"] = code.c_str();
    payload["newPassword"] = newPassword.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createChangeEmailPayload(const std::string &email, const std::string &newEmail)
{
    QJsonObject payload;
    payload["apiId"] = static_cast<int>(FirebaseApi::ChangeEmail);
    payload["email"] = email.c_str();
    payload["newEmail"] = newEmail.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createUpdateProfilePayload(const std::string &email, const std::string &displayName, const std::string &photoUrl)
{
    QJsonObject payload;
    payload["apiId"] = static_cast<int>(FirebaseApi::UpdateProfile);
    payload["email"] = email.c_str();
    payload["displayName"] = displayName.c_str();
    payload["photoUrl"] = photoUrl.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createGetUserDataPayload(const std::string &email)
{
    QJsonObject payload;
    payload["apiId"] = static_cast<int>(FirebaseApi::GetUserData);
    payload["email"] = email.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createExchangeCustomTokenPayload(const std::string &customToken)
{
    QJsonObject payload;
    payload["apiId"] = static_cast<int>(FirebaseApi::ExchangeCustomToken);
    payload["customToken"] = customToken.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createExchangeRefreshTokenPayload(const std::string &refreshToken)
{
    QJsonObject payload;
    payload["apiId"] = static_cast<int>(FirebaseApi::ExchangeRefreshToken);
    payload["refreshToken"] = refreshToken.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createSignInWithGooglePayload(const std::string &accessToken)
{
    QJsonObject payload;
    payload["apiId"] = static_cast<int>(FirebaseApi::SignInWithGoogle);
    payload["accessToken"] = accessToken.c_str();
    return payload;
}

FirebasePayloadFactory::SignInEmailPasswordResData FirebasePayloadFactory::parseSignInEmailPasswordResPayload(const QJsonObject &payload)
{
    SignInEmailPasswordResData resPayload;
    resPayload.idToken = payload["idToken"].toString();
    resPayload.email = payload["email"].toString();
    resPayload.refreshToken = payload["refreshToken"].toString();
    resPayload.expiresIn = payload["expiresIn"].toString();
    resPayload.localId = payload["localId"].toString();
    return resPayload;
}

FirebasePayloadFactory::SignUpEmailPasswordResData FirebasePayloadFactory::parseSignUpEmailPasswordResPayload(const QJsonObject &payload)
{
    SignUpEmailPasswordResData resPayload;
    resPayload.idToken = payload["idToken"].toString();
    resPayload.email = payload["email"].toString();
    resPayload.refreshToken = payload["refreshToken"].toString();
    resPayload.expiresIn = payload["expiresIn"].toString();
    resPayload.localId = payload["localId"].toString();
    return resPayload;
}

FirebasePayloadFactory::SignInAnounymousResData FirebasePayloadFactory::parseSignInAnounymousResPayload(const QJsonObject &payload)
{
    SignInAnounymousResData resPayload;
    resPayload.idToken = payload["idToken"].toString();
    resPayload.refreshToken = payload["refreshToken"].toString();
    resPayload.expiresIn = payload["expiresIn"].toString();
    resPayload.localId = payload["localId"].toString();
    return resPayload;
}

FirebasePayloadFactory::ChangePasswordResData FirebasePayloadFactory::parseChangePasswordResPayload(const QJsonObject &payload)
{
    ChangePasswordResData resPayload;
    resPayload.email = payload["email"].toString();
    resPayload.localId = payload["localId"].toString();
    resPayload.pwHash = payload["pwHash"].toString();
    resPayload.providerUserInfos = payload["providerUserInfos"].toArray();
    resPayload.idToken = payload["idToken"].toString();
    resPayload.refreshToken = payload["refreshToken"].toString();
    resPayload.expiresIn = payload["expiresIn"].toString();
    return resPayload;
}

FirebasePayloadFactory::SendPwResetEmailResData FirebasePayloadFactory::parseSendPwResetEmailResPayload(const QJsonObject &payload)
{
    SendPwResetEmailResData resPayload;
    resPayload.email = payload["email"].toString();
    resPayload.requestType = payload["requestType"].toString();
    return resPayload;
}

FirebasePayloadFactory::VerifyPwResetCodeResData FirebasePayloadFactory::parseVerifyPwResetCodeResPayload(const QJsonObject &payload)
{
    VerifyPwResetCodeResData resPayload;
    resPayload.email = payload["email"].toString();
    resPayload.requestType = payload["requestType"].toString();
    return resPayload;
}

FirebasePayloadFactory::ConfirmPwResetResData FirebasePayloadFactory::parseConfirmPwResetResPayload(const QJsonObject &payload)
{
    ConfirmPwResetResData resPayload;
    resPayload.email = payload["email"].toString();
    resPayload.requestType = payload["requestType"].toString();
    return resPayload;
}

FirebasePayloadFactory::ChangeEmailResData FirebasePayloadFactory::parseChangeEmailResPayload(const QJsonObject &payload)
{
    ChangeEmailResData resPayload;
    resPayload.localId = payload["localId"].toString();
    resPayload.email = payload["email"].toString();
    resPayload.pwHash = payload["pwHash"].toString();
    resPayload.providerUserInfos = payload["providerUserInfos"].toArray();
    resPayload.idToken = payload["idToken"].toString();
    resPayload.refreshToken = payload["refreshToken"].toString();
    resPayload.expiresIn = payload["expiresIn"].toString();
    return resPayload;
}

FirebasePayloadFactory::UpdateProfileResData FirebasePayloadFactory::parseUpdateProfileResPayload(const QJsonObject &payload)
{
    UpdateProfileResData resPayload;
    resPayload.email = payload["email"].toString();
    resPayload.localId = payload["localId"].toString();
    resPayload.displayName = payload["displayName"].toString();
    resPayload.photoUrl = payload["photoUrl"].toString();
    resPayload.pwHash = payload["pwHash"].toString();
    resPayload.providerUserInfos = payload["providerUserInfos"].toArray();
    resPayload.idToken = payload["idToken"].toString();
    resPayload.refreshToken = payload["refreshToken"].toString();
    resPayload.expiresIn = payload["expiresIn"].toString();
    return resPayload;
}

FirebasePayloadFactory::ExchangeCustomTokenResData FirebasePayloadFactory::parseExchangeCustomTokenResPayload(const QJsonObject &payload)
{
    ExchangeCustomTokenResData resPayload;
    resPayload.idToken = payload["idToken"].toString();
    resPayload.refreshToken = payload["refreshToken"].toString();
    resPayload.expiresIn = payload["expiresIn"].toString();
    return resPayload;
}

FirebasePayloadFactory::ExchangeRefreshTokenResData FirebasePayloadFactory::parseExchangeRefreshTokenResPayload(const QJsonObject &payload)
{
    ExchangeRefreshTokenResData resPayload;
    resPayload.idToken = payload["idToken"].toString();
    resPayload.refreshToken = payload["refreshToken"].toString();
    resPayload.expiresIn = payload["expiresIn"].toString();
    return resPayload;
}

FirebasePayloadFactory::GoogleAccessTokenResData FirebasePayloadFactory::parseGoogleAccessTokenResPayload(const QJsonObject &payload)
{
    GoogleAccessTokenResData resPayload;
    resPayload.accessToken = payload["accessToken"].toString();
    resPayload.tokenType = payload["tokenType"].toString();
    resPayload.expiresIn = payload["expiresIn"].toString();
    resPayload.refreshToken = payload["refreshToken"].toString();
    resPayload.scope = payload["scope"].toString();
    return resPayload;
}