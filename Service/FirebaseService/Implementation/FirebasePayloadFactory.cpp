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
    payload["email"] = email.c_str();
    payload["password"] = password.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createSignUpPayload(const std::string &email, const std::string &password)
{
    QJsonObject payload;
    payload["email"] = email.c_str();
    payload["password"] = password.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createChangePasswordPayload(const std::string &email, const std::string &password)
{
    QJsonObject payload;
    payload["email"] = email.c_str();
    payload["password"] = password.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createSendPwResetEmailPayload(const std::string &email)
{
    QJsonObject payload;
    payload["email"] = email.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createVerifyPwResetCodePayload(const std::string &email, const std::string &code)
{
    QJsonObject payload;
    payload["email"] = email.c_str();
    payload["code"] = code.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createConfirmPwResetPayload(const std::string &email, const std::string &code, const std::string &newPassword)
{
    QJsonObject payload;
    payload["email"] = email.c_str();
    payload["code"] = code.c_str();
    payload["newPassword"] = newPassword.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createChangeEmailPayload(const std::string &email, const std::string &newEmail)
{
    QJsonObject payload;
    payload["email"] = email.c_str();
    payload["newEmail"] = newEmail.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createUpdateProfilePayload(const std::string &email, const std::string &displayName, const std::string &photoUrl)
{
    QJsonObject payload;
    payload["email"] = email.c_str();
    payload["displayName"] = displayName.c_str();
    payload["photoUrl"] = photoUrl.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createGetUserDataPayload(const std::string &email)
{
    QJsonObject payload;
    payload["email"] = email.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createExchangeCustomTokenPayload(const std::string &customToken)
{
    QJsonObject payload;
    payload["customToken"] = customToken.c_str();
    return payload;
}

QJsonObject FirebasePayloadFactory::createExchangeRefreshTokenPayload(const std::string &refreshToken)
{
    QJsonObject payload;
    payload["refreshToken"] = refreshToken.c_str();
    return payload;
}