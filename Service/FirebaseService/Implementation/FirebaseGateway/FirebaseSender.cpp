/*
* FirebaseSender.cpp
* Author: Trung La
* Date: 2024-12-01
* This is the implementation of the FirebaseSender class
*/

#include "FirebaseSender.h"

#include <QNetworkRequest>

FirebaseSender::FirebaseSender(QObject *parent)
    : QObject(parent)
{
    connect(&m_networkManager, &QNetworkAccessManager::finished, this, &FirebaseSender::onReplyFinished);
}

FirebaseSender::~FirebaseSender()
{
}

void FirebaseSender::postRequest(const QString &url, const QJsonObject &payload)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();

    m_networkManager.post(request, data);
}

void FirebaseSender::onReplyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QString responseBody = reply->readAll();
        emit requestFinished(statusCode, responseBody);
    } else {
        emit requestError(reply->errorString());
    }

    reply->deleteLater();
}