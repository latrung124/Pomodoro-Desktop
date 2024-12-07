/*
* FirebaseGatewayManager.cpp
* Author: Trung La
* Date: 2024-12-01
* This class is a manager class for FirebaseGateway
*/

#include "FirebaseGatewayManager.h"
#include "FirebaseGateway/FirebaseSender.h"
#include "Handler/Firebase//FirebaseResponseHandler.h"
#include "Core/Helper/Firebase/FirebaseHandlerHelper.h"

#include <QDebug>

FirebaseGatewayManager::FirebaseGatewayManager()
{
    m_sender = new FirebaseSender();
    m_sender->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, m_sender, &QObject::deleteLater);
    connect(this, &FirebaseGatewayManager::initWrappers, m_sender, &FirebaseSender::onInitWrapper);
    workerThread.start();
    emit initWrappers();

    startConnection();
}

FirebaseGatewayManager::~FirebaseGatewayManager()
{
    endConnection();
    workerThread.quit();
    workerThread.wait();
}

void FirebaseGatewayManager::startConnection()
{
    connect(this, &FirebaseGatewayManager::operate, m_sender, &FirebaseSender::postRequest);
}

void FirebaseGatewayManager::endConnection()
{
    disconnect(this, &FirebaseGatewayManager::operate, m_sender, &FirebaseSender::postRequest);
}

void FirebaseGatewayManager::onPostRequestFinished(const FirebaseResMsgData &data)
{
    qDebug() << "FirebaseGatewayManager::onPostRequestFinished() called";
    if (auto firebaseResponseHandler = utils::firebase::getServiceHandler<FirebaseResponseHandler>().lock(); firebaseResponseHandler) {
        firebaseResponseHandler->enqueueMessage(data);
    }
}
