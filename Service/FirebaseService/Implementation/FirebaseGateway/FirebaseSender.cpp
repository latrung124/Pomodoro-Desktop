/*
* FirebaseSender.cpp
* Author: Trung La
* Date: 2024-12-01
* This is the implementation of the FirebaseSender class
*/

#include "FirebaseSender.h"
#include "FirebaseGateway/AuthWrapper.h"
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
}

void FirebaseSender::endConnection()
{
    disconnect(m_authWrapper.get(), &AuthWrapper::postSignInFinished,
               this, &FirebaseSender::onPostRequestFinished);
}

void FirebaseSender::postRequest(const QJsonObject &payload)
{
    // Need to refactor this part to handle more type of post requests
    m_authWrapper->postSignIn(payload);
}

void FirebaseSender::onInitWrapper()
{
    m_authWrapper = std::make_unique<AuthWrapper>();

    startConnection();
}

void FirebaseSender::onPostRequestFinished(const FirebaseResMsgData &data)
{
    qDebug() << "FirebaseSender::onPostRequestFinished() called";
    m_gatewayManager->onPostRequestFinished(data);
}
