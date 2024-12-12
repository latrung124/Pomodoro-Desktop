/*
* FirebaseGatewayManager.cpp
* Author: Trung La
* Date: 2024-12-01
* This class is a manager class for FirebaseGateway
*/

#include "FirebaseGatewayManager.h"
#include "FirebaseGateway/FirebaseSender.h"
#include "FirebaseListenerManager.h"
#include "Listener/FirebaseAuthListenerImpl.h"

#include <QDebug>

FirebaseGatewayManager::FirebaseGatewayManager(QObject *parent)
 : QObject(parent)
{

}

FirebaseGatewayManager::~FirebaseGatewayManager()
{
    endConnection();
    workerThread.quit();
    workerThread.wait();
}

void FirebaseGatewayManager::init()
{
    m_sender = new FirebaseSender(this);
    m_sender->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, m_sender, &QObject::deleteLater);
    connect(this, &FirebaseGatewayManager::initWrappers, m_sender, &FirebaseSender::onInitWrapper);
    workerThread.start();
    emit initWrappers();

    startConnection();
}

void FirebaseGatewayManager::startConnection()
{
    connect(this, &FirebaseGatewayManager::operate, m_sender, &FirebaseSender::postRequest);
}

void FirebaseGatewayManager::endConnection()
{
    disconnect(this, &FirebaseGatewayManager::operate, m_sender, &FirebaseSender::postRequest);
}

void FirebaseGatewayManager::onPostRequestFinished(const FirebaseResMsgData &data) const
{
    qDebug() << "FirebaseGatewayManager::onPostRequestFinished() called";
    auto listenerManager = m_listenerManager.lock();
    if (listenerManager) {
        listenerManager->notifyListeners<FirebaseAuthListenerImpl>(data);
    }
}

void FirebaseGatewayManager::setFirebaseListenerManager(std::shared_ptr<FirebaseListenerManager> listenerManager)
{
    m_listenerManager = listenerManager;
}
