/*
* AuthWrapper.h
* Author: Trung La
* Date: 2024-12-04
* This is the implementation of the AuthWrapper class
*/

#ifndef AUTHWRAPPER_H
#define AUTHWRAPPER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequestFactory>
#include <QRestAccessManager>
#include <QRestReply>

#include <memory>

namespace firebase_utils::API_Usage {

struct FirebaseResMsgData;

}

class AuthWrapper : public QObject
{
    Q_OBJECT
public:
    using FirebaseResMsgData = firebase_utils::API_Usage::FirebaseResMsgData;

    AuthWrapper(QObject *parent = nullptr);
    ~AuthWrapper();

    void postSignIn(const QJsonObject &payload);

    bool sslSupport();
    void setUrl(const QString &url);

signals:
    void postSignInFinished(const FirebaseResMsgData &data);

private:
    void handleReplyFinished(QRestReply &reply);

    QNetworkAccessManager m_networkManager;
    std::unique_ptr<QNetworkRequestFactory> m_requestFactory;
    std::unique_ptr<QRestAccessManager> m_restAccessManager;
};

#endif // AUTHWRAPPER_H