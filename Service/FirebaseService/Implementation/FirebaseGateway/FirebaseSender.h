/*
* FirebaseSender.h
* Author: Trung La
* Date: 2024-12-01
* This is the implementation of the FirebaseSender class
*/

#ifndef FIREBASESENDER_H
#define FIREBASESENDER_H

#include <QObject>
#include <QJsonObject>

#include <memory>

class AuthWrapper;

namespace firebase_utils::API_Usage {

struct FirebaseResMsgData;

}

class FirebaseSender : public QObject
{
    Q_OBJECT
public:
    using FirebaseResMsgData = firebase_utils::API_Usage::FirebaseResMsgData;
    explicit FirebaseSender(QObject *parent = nullptr);
    ~FirebaseSender();

    void postRequest(const QJsonObject &payload);

public slots:
    void onInitWrapper();
    void onPostRequestFinished(const FirebaseResMsgData &data);

private:
    void startConnection();
    void endConnection();

    std::unique_ptr<AuthWrapper> m_authWrapper;
};

#endif // FIREBASESENDER_H
