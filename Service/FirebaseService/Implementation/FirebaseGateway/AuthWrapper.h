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

#include <memory>

class AuthWrapper : public QObject
{
    Q_OBJECT
public:
    AuthWrapper(QObject *parent = nullptr);
    ~AuthWrapper();

    void postSignIn(const QJsonObject &payload);

    bool sslSupport();
    void setUrl(const QString &url);

private:
    QNetworkAccessManager m_networkManager;
    std::unique_ptr<QNetworkRequestFactory> m_requestFactory;
    std::unique_ptr<QRestAccessManager> m_restAccessManager;
};

#endif // AUTHWRAPPER_H