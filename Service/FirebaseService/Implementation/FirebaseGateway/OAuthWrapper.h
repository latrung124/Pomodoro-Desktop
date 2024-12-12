/*
* OAuthWrapper.h
* Author: Trung La
* Date: 2024-12-10
* This is a wrapper class for OAuth authentication providers
*/

#ifndef OAUTHWRAPPER_H
#define OAUTHWRAPPER_H

#include <QOAuthHttpServerReplyHandler>
#include <QOAuth2AuthorizationCodeFlow>
#include <QObject>
#include <QString>

class OAuthWrapper : public QObject
{
    Q_OBJECT
public:
    OAuthWrapper(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~OAuthWrapper() = default;

    OAuthWrapper(const OAuthWrapper &) = delete;
    OAuthWrapper &operator=(const OAuthWrapper &) = delete;
    OAuthWrapper(OAuthWrapper &&) = delete;
    OAuthWrapper &operator=(OAuthWrapper &&) = delete;

    virtual void signIn() = 0;

protected:
    QOAuth2AuthorizationCodeFlow *m_oauth2 = nullptr;
    QOAuthHttpServerReplyHandler *m_replyHandler = nullptr;
};

#endif // OAUTHWRAPPER_H