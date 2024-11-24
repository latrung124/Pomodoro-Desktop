/*
* GoogleOAuth.h
* Author: Trung La
* Date: 2024-11-24
* This is an implementation class for Google OAuth authentication provider
*/

#ifndef GOOGLEOAUTH_H
#define GOOGLEOAUTH_H

#include "FirebaseUtils.h"

#include <QNetworkAccessManager>
#include <QTcpServer>

#include <string>

class GoogleOAuth : public QObject
{
    Q_OBJECT
public:
    explicit GoogleOAuth(QObject* parent = nullptr);
    ~GoogleOAuth() = default;

    bool requestAccessToken();
    bool exchangeCodeForToken(const std::string& authorizationCode);

signals:
    void googleAccessTokenReceived(const GoogleAccessToken& accessToken);

private:
    bool loadConfig();
    std::string generateAuthorizationUrl();

    OAuthConfig m_oauthConfig;
    bool m_isConfigAvailable;
    QNetworkAccessManager m_networkManager;
    QTcpServer* m_tcpServer;
    GoogleAccessToken m_googleAccessToken;
};

#endif // GOOGLEOAUTH_H