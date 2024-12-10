/*
* GoogleOAuthWrapper.h
* Author: Trung La
* Date: 2024-12-10
* This is a wrapper class for Google OAuth authentication provider
*/

#ifndef GOOGLEOAUTHWRAPPER_H
#define GOOGLEOAUTHWRAPPER_H

#include "FirebaseUtils.h"
#include "FirebaseGateway/OAuthWrapper.h"

#include <optional>

class GoogleOAuthWrapper : public OAuthWrapper
{
    Q_OBJECT
public:
    using FirebaseResMsgData = firebase_utils::API_Usage::FirebaseResMsgData;
    GoogleOAuthWrapper(QObject* parent = nullptr);
    ~GoogleOAuthWrapper();

    void signIn() override;

signals:
    void googleAuthenticationSuccess(const FirebaseResMsgData &data);

private slots:
    void handleAuthStatusChanged(const QAbstractOAuth::Status& status);
    void handleTokenReceived();

private:
    bool loadConfig();
    void setupOAuth2();
    void getUserInfo();

    std::optional<OAuthConfig> m_oauthConfig;
    QString m_accessToken;
};

#endif // GOOGLEOAUTHWRAPPER_H
