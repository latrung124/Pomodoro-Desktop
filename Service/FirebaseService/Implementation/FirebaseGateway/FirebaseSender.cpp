/*
* FirebaseSender.cpp
* Author: Trung La
* Date: 2024-12-01
* This is the implementation of the FirebaseSender class
*/

#include "FirebaseSender.h"
#include "FirebaseGateway/AuthWrapper.h"

#include <QNetworkRequest>
#include <QJsonDocument>

FirebaseSender::FirebaseSender(QObject *parent)
    : QObject(parent)
{
}

FirebaseSender::~FirebaseSender()
{
}

void FirebaseSender::postRequest(const QJsonObject &payload)
{
    m_authWrapper->postSignIn(payload);
}

void FirebaseSender::onInitWrapper()
{
    m_authWrapper = std::make_unique<AuthWrapper>();
}
