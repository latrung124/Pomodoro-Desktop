/*
* FirebaseSender.h
* Author: Trung La
* Date: 2024-12-01
* This is the implementation of the FirebaseSender class
*/

#ifndef FIREBASESENDER_H
#define FIREBASESENDER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>

class FirebaseSender : public QObject
{
Q_OBJECT
public:
    explicit FirebaseSender(QObject *parent = nullptr);
    ~FirebaseSender();

    void postRequest(const QJsonObject &payload);

signals:
    void requestFinished(int statusCode, const QString &responseBody);
    void requestError(const QString &error);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager m_networkManager;
};

#endif // FIREBASESENDER_H
