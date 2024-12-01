/*
* FirebaseGatewayManager.cpp
* Author: Trung La
* Date: 2024-12-01
* This class is a manager class for FirebaseGateway
*/

#include "FirebaseGatewayManager.h"

#include <QDebug>

FirebaseGatewayManager::FirebaseGatewayManager(QObject *parent)
    : QObject(parent)
{
    m_authSender = std::make_shared<FirebaseSender>();

    connect(m_authSender.get(), &FirebaseSender::requestFinished, this, &FirebaseGatewayManager::onAuthRequestFinished);
}

FirebaseGatewayManager::~FirebaseGatewayManager()
{
}

std::weak_ptr<FirebaseSender> FirebaseGatewayManager::getFirebaseAuthSender() const
{
    return m_authSender;
}

void FirebaseGatewayManager::onAuthRequestFinished(int statusCode, const QString &responseBody)
{
    qDebug() << "FirebaseGatewayManager::onAuthRequestFinished() called: " << statusCode << " " << responseBody;
}

void FirebaseGatewayManager::onAuthRequestError(const QString &error)
{
    qDebug() << "FirebaseGatewayManager::onAuthRequestError() called: " << error;
}