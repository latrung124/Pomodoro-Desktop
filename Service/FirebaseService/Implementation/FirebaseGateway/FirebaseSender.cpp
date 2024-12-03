/*
* FirebaseSender.cpp
* Author: Trung La
* Date: 2024-12-01
* This is the implementation of the FirebaseSender class
*/

#include "FirebaseSender.h"

#include <QNetworkRequest>
#include <QJsonDocument>

FirebaseSender::FirebaseSender(QObject *parent)
    : QObject(parent)
{
    connect(&m_networkManager, &QNetworkAccessManager::finished, this, &FirebaseSender::onReplyFinished);
}

FirebaseSender::~FirebaseSender()
{
}

void FirebaseSender::postRequest(const QJsonObject &payload)
{
}

void FirebaseSender::onReplyFinished(QNetworkReply *reply)
{
}
