/*
* FirebasePayloadFactory.h
* Author: Trung La
* Date: 2024-12-05
*/

#ifndef FIREBASEPAYLOADFACTORY_H
#define FIREBASEPAYLOADFACTORY_H

#include <QJsonObject>

class FirebasePayloadFactory
{
public:
    FirebasePayloadFactory() = default;
    ~FirebasePayloadFactory() = default;

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
};

#endif // FIREBASEPAYLOADFACTORY_H