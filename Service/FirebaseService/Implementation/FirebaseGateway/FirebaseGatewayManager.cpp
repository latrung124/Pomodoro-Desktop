/*
* FirebaseGatewayManager.cpp
* Author: Trung La
* Date: 2024-12-01
* This class is a manager class for FirebaseGateway
*/

#include "FirebaseGatewayManager.h"
#include "FirebaseGateway/FirebaseSender.h"

#include <QDebug>

FirebaseGatewayManager::FirebaseGatewayManager()
{
    FirebaseSender *sender = new FirebaseSender();
    sender->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, sender, &QObject::deleteLater);
    connect(this, &FirebaseGatewayManager::initWrappers, sender, &FirebaseSender::onInitWrapper);
    workerThread.start();
    emit initWrappers();

    connect(this, &FirebaseGatewayManager::operate, sender, &FirebaseSender::postRequest);
}

FirebaseGatewayManager::~FirebaseGatewayManager()
{
    workerThread.quit();
    workerThread.wait();
}