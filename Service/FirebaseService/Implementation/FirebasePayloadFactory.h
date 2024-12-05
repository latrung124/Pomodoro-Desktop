/*
* FirebasePayloadFactory.h
* Author: Trung La
* Date: 2024-12-05
*/

#ifndef FIREBASEPAYLOADFACTORY_H
#define FIREBASEPAYLOADFACTORY_H

#include "FirebaseUtils.h"

#include <QJsonObject>

class FirebasePayloadFactory
{
public:
    FirebasePayloadFactory() = default;
    ~FirebasePayloadFactory() = default;

    using SignInEmailPasswordResData = firebase_utils::API_Usage::SignInEmailPasswordResData;
    using SignUpEmailPasswordResData = firebase_utils::API_Usage::SignUpEmailPasswordResData;
    using SignInAnounymousResData = firebase_utils::API_Usage::SignInAnounymousResData;
    using ChangePasswordResData = firebase_utils::API_Usage::ChangePasswordResData;
    using SendPwResetEmailResData = firebase_utils::API_Usage::SendPwResetEmailResData;
    using VerifyPwResetCodeResData = firebase_utils::API_Usage::VerifyPwResetCodeResData;
    using ConfirmPwResetResData = firebase_utils::API_Usage::ConfirmPwResetResData;
    using ChangeEmailResData = firebase_utils::API_Usage::ChangeEmailResData;
    using UpdateProfileResData = firebase_utils::API_Usage::UpdateProfileResData;
    using ExchangeCustomTokenResData = firebase_utils::API_Usage::ExchangeCustomTokenResData;
    using ExchangeRefreshTokenResData = firebase_utils::API_Usage::ExchangeRefreshTokenResData;

    static QJsonObject createSignInPayload(const std::string &email, const std::string &password);
    static QJsonObject createSignUpPayload(const std::string &email, const std::string &password);
    static QJsonObject createChangePasswordPayload(const std::string &email, const std::string &password);
    static QJsonObject createSendPwResetEmailPayload(const std::string &email);
    static QJsonObject createVerifyPwResetCodePayload(const std::string &email, const std::string &code);
    static QJsonObject createConfirmPwResetPayload(const std::string &email, const std::string &code, const std::string &newPassword);
    static QJsonObject createChangeEmailPayload(const std::string &email, const std::string &newEmail);
    static QJsonObject createUpdateProfilePayload(const std::string &email, const std::string &displayName, const std::string &photoUrl);
    static QJsonObject createGetUserDataPayload(const std::string &email);
    static QJsonObject createExchangeCustomTokenPayload(const std::string &customToken);
    static QJsonObject createExchangeRefreshTokenPayload(const std::string &refreshToken);

    static SignInEmailPasswordResData parseSignInEmailPasswordResPayload(const QJsonObject &payload);
    static SignUpEmailPasswordResData parseSignUpEmailPasswordResPayload(const QJsonObject &payload);
    static SignInAnounymousResData parseSignInAnounymousResPayload(const QJsonObject &payload);
    static ChangePasswordResData parseChangePasswordResPayload(const QJsonObject &payload);
    static SendPwResetEmailResData parseSendPwResetEmailResPayload(const QJsonObject &payload);
    static VerifyPwResetCodeResData parseVerifyPwResetCodeResPayload(const QJsonObject &payload);
    static ConfirmPwResetResData parseConfirmPwResetResPayload(const QJsonObject &payload);
    static ChangeEmailResData parseChangeEmailResPayload(const QJsonObject &payload);
    static UpdateProfileResData parseUpdateProfileResPayload(const QJsonObject &payload);
    static ExchangeCustomTokenResData parseExchangeCustomTokenResPayload(const QJsonObject &payload);
    static ExchangeRefreshTokenResData parseExchangeRefreshTokenResPayload(const QJsonObject &payload);
};

#endif // FIREBASEPAYLOADFACTORY_H