/*
* AuthWrapper.cpp
* Author: Trung La
* Date: 2024-12-04
* This is the implementation of the AuthWrapper class
*/

#include "FirebaseGateway/AuthWrapper.h"
#include <QHttpHeaders>
#include <QJsonDocument>

#if QT_CONFIG(ssl)
#include <QtNetwork/qsslsocket.h>
#endif

using namespace Qt::StringLiterals;

AuthWrapper::AuthWrapper(QObject *parent)
    : QObject(parent)
    , m_requestFactory(std::make_unique<QNetworkRequestFactory>())
    , m_restAccessManager(std::make_unique<QRestAccessManager>(&m_networkManager))
{
    QHttpHeaders headers;
    headers.append("Content-Type"_L1, "application/json"_L1);
    m_requestFactory->setCommonHeaders(headers);
    m_requestFactory->setBaseUrl(QUrl("https://identitytoolkit.googleapis.com/v1"_L1));
}

AuthWrapper::~AuthWrapper()
{
}

bool AuthWrapper::sslSupport()
{
#if QT_CONFIG(ssl)
    return QSslSocket::supportsSsl();
#else
    return false;
#endif
}

void AuthWrapper::postSignIn(const QJsonObject &payload)
{
    QString query = QString("accounts:signInWithPassword?key=%1"_L1).arg("key");
    QNetworkRequest request = m_requestFactory->createRequest(query);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"_L1);
    m_restAccessManager->post(request, QJsonDocument(payload).toJson());
}

void AuthWrapper::setUrl(const QString &url)
{
    m_requestFactory->setBaseUrl(url);
}
