/*
* FirebaseSender.cpp
* Author: Trung La
* Date: 2024-12-01
* This is the implementation of the FirebaseSender class
*/

#include "FirebaseSender.h"
#include "FirebaseGateway/AuthWrapper.h"
#include "FirebaseGateway/GoogleOAuthWrapper.h"
#include "FirebaseUtils.h"
#include "FirebaseGateway/FirebaseGatewayManager.h"

#include <QNetworkRequest>
#include <QJsonDocument>

FirebaseSender::FirebaseSender(const FirebaseGatewayManager *gatewayManager, QObject *parent)
    : QObject(parent)
    , m_gatewayManager(gatewayManager)
{
}

FirebaseSender::~FirebaseSender()
{
    endConnection();
}

void FirebaseSender::startConnection()
{
    connect(m_authWrapper.get(), &AuthWrapper::postSignInFinished,
            this, &FirebaseSender::onPostRequestFinished);
    connect(m_authWrapper.get(), &AuthWrapper::postSignUpFinished,
            this, &FirebaseSender::onPostRequestFinished);
    connect(m_authWrapper.get(), &AuthWrapper::postUpdatePasswordFinished,
            this, &FirebaseSender::onPostRequestFinished);
    connect(m_googleOAuthWrapper.get(), &GoogleOAuthWrapper::googleAuthenticationSuccess,
            this, &FirebaseSender::onPostOAuthRequestFinished);
}

void FirebaseSender::endConnection()
{
    disconnect(m_authWrapper.get(), &AuthWrapper::postSignInFinished,
               this, &FirebaseSender::onPostRequestFinished);
    disconnect(m_authWrapper.get(), &AuthWrapper::postSignUpFinished,
               this, &FirebaseSender::onPostRequestFinished);
    disconnect(m_authWrapper.get(), &AuthWrapper::postUpdatePasswordFinished,
               this, &FirebaseSender::onPostRequestFinished);
}

void FirebaseSender::postRequest(const QJsonObject &payload)
{
    using FirebaseApi = firebase_utils::API_Usage::FirebaseApi;
    uint16_t apiId = payload.value("apiId").toInt();
    switch (static_cast<FirebaseApi>(apiId))
    {
    case FirebaseApi::SignInEmailPassword:
        m_authWrapper->postSignIn(payload);
        break;
    case FirebaseApi::SignUpEmailPassword:
        m_authWrapper->postSignUp(payload);
        break;
    case FirebaseApi::ChangePassword:
        m_authWrapper->postUpdatePassword(payload);
        break;
    case FirebaseApi::SignInWithGoogle:
        m_googleOAuthWrapper->signIn();
        break;
    default:
        break;
    }
}

void FirebaseSender::onInitWrapper()
{
    m_authWrapper = std::make_unique<AuthWrapper>();
    m_googleOAuthWrapper = std::make_unique<GoogleOAuthWrapper>();

    startConnection();
}

void FirebaseSender::onPostRequestFinished(const FirebaseResMsgData &data)
{
    qDebug() << "FirebaseSender::onPostRequestFinished() called";
    m_gatewayManager->onPostRequestFinished(data);
}

void FirebaseSender::onPostOAuthRequestFinished(const FirebaseResMsgData &data)
{
    qDebug() << "FirebaseSender::onPostOAuthRequestFinished() called";
    m_gatewayManager->onPostRequestFinished(data);
}
