/*
* AuthWrapper.cpp
* Author: Trung La
* Date: 2024-12-04
* This is the implementation of the AuthWrapper class
*/

#include "FirebaseHelper.h"
#include "FirebaseGateway/AuthWrapper.h"
#include "FirebaseUtils.h"
#include "FirebaseGateway/FirebaseSender.h"

#include <QHttpHeaders>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#if QT_CONFIG(ssl)
#include <QtNetwork/qsslsocket.h>
#endif

AuthWrapper::AuthWrapper(QObject *parent)
    : QObject(parent)
    , m_requestFactory(std::make_unique<QNetworkRequestFactory>())
    , m_restAccessManager(std::make_unique<QRestAccessManager>(&m_networkManager))
{
    QHttpHeaders headers;
    headers.append("Content-Type"_L1, "application/json"_L1);
    m_requestFactory->setCommonHeaders(headers);
    m_requestFactory->setBaseUrl(firebase_utils::API_Usage::gFirebaseBaseUrl);
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
    using namespace FirebaseGateway::Helper;
    QString apiKey = getCurrentApiKey().c_str();
    if (apiKey.isEmpty()) {
        qWarning() << "API key is empty";
        return;
    }

    QString path = QString(getFirebaseApiPath(firebase_utils::API_Usage::FirebaseApi::SignInEmailPassword)).arg(apiKey);
    QNetworkRequest request = m_requestFactory->createRequest(path);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"_L1);
    m_restAccessManager->post(request, QJsonDocument(payload), this, [this](QRestReply &reply) {
        //print thread id:
        handleReplyFinished(reply);
    });
}

void AuthWrapper::handleReplyFinished(QRestReply &reply)
{
    using namespace FirebaseGateway::Helper;
    if (reply.error() == QNetworkReply::NoError) {
        auto jsonOpt = reply.readJson();
        if (!jsonOpt.has_value()) {
            qWarning() << "Failed to parse JSON response";
            return;
        }
        QJsonDocument jsonResponse = jsonOpt.value();
        QJsonObject jsonObject = jsonResponse.object();

        // Extract fields from the JSON response
        FirebaseResMsgData msgData;
        msgData.api = firebase_utils::API_Usage::FirebaseApi::SignInEmailPassword;
        auto localId = jsonObject.value("localId").toString();
        auto idToken = jsonObject.value("idToken").toString();
        auto refreshToken = jsonObject.value("refreshToken").toString();
        auto expiresIn = jsonObject.value("expiresIn").toString();
        auto registered = jsonObject.value("registered").toBool();
        auto email = jsonObject.value("email").toString();
        msgData.data = firebase_utils::API_Usage::SignInEmailPasswordResData{
            .idToken = idToken,
            .email = email,
            .refreshToken = refreshToken,
            .expiresIn = expiresIn,
            .localId = localId,
            .isRegistered = registered
        };
        qDebug() << "Post SignIn successful!";
        emit postSignInFinished(msgData);
    } else {
        // Error
        qDebug() << "Post SignIn failed!";
        qDebug() << "Error:" << reply.errorString();

        // Attempt to parse the error response
        auto errorOpt = reply.readJson();
        if (!errorOpt.has_value()) {
            qWarning() << "Failed to parse JSON error response";
            return;
        }
        QJsonDocument jsonError = errorOpt.value();
        QJsonObject jsonObject = jsonError.object();
        QString errorMessage = jsonObject.value("error").toObject().value("message").toString();

        if (!errorMessage.isEmpty()) {
            qDebug() << "Error message:" << errorMessage;
        }
        emit postSignInFinished(FirebaseResMsgData{});
    }
}

void AuthWrapper::setUrl(const QString &url)
{
    m_requestFactory->setBaseUrl(url);
}
