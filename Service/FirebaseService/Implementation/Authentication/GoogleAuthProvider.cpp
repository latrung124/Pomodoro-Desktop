/*
* GoogleAuthProvider.cpp
* Author: Trung La
* Date: 2024-11-24
* This is a concrete class for Google authentication provider
*/

#include "GoogleAuthProvider.h"
#include "FirebaseAuthentication.h"
#include "FirebaseGateway/FirebaseGatewayManager.h"
#include "FirebasePayloadFactory.h"

#include <QJsonObject>
#include <QDebug>

bool GoogleAuthProvider::signIn()
{
    qDebug() << "GoogleAuthProvider::signIn() called";
    QJsonObject payload = FirebasePayloadFactory::createSignInWithGooglePayload();
    if (auto gatewayManager = m_firebase->getGatewayManager().lock(); gatewayManager)
    {
        gatewayManager->operate(payload);
    }
    else
    {
        qWarning() << "Failed to get FirebaseGatewayManager";
    }
    return true;
}
