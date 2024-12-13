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
#include <QUrl>
#include <QNetworkAccessManager>
#include <QTcpServer>

#include <optional>

class GoogleOAuthWrapper : public OAuthWrapper
{
    Q_OBJECT
public:
    using FirebaseResMsgData = firebase_utils::API_Usage::FirebaseResMsgData;
    using GoogleAccessTokenResData = firebase_utils::API_Usage::GoogleAccessTokenResData;
    using FirebaseApi = firebase_utils::API_Usage::FirebaseApi;

    GoogleOAuthWrapper(QObject* parent = nullptr);
    ~GoogleOAuthWrapper();

    void signIn() override;

signals:
    void googleAuthenticationSuccess(const FirebaseResMsgData &data);

private:
    bool loadConfig();
    bool requestAccessToken();
    bool openListenServer();
    bool openBrowser(const QUrl& authorizationUrl);
    bool exchangeCodeForToken(const std::string& authorizationCode);
    std::string generateAuthorizationUrl();
    quint16 getPort() const;

    std::optional<OAuthConfig> m_oauthConfig;
    QNetworkAccessManager m_networkManager;
    QTcpServer* m_tcpServer;
    GoogleAccessTokenResData m_googleAccessToken;
    quint16 m_port;
    bool m_loadedConfig;
};

#endif // GOOGLEOAUTHWRAPPER_H
