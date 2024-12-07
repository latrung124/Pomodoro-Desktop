/*
* FirebaseGatewayManager.h
* Author: Trung La
* Date: 2024-12-01
* This class is a manager class for FirebaseGateway
*/

#ifndef FIREBASEGATEWAYMANAGER_H
#define FIREBASEGATEWAYMANAGER_H

#include <QThread>
#include <QJsonObject>
#include <memory>

namespace firebase_utils::API_Usage {

struct FirebaseResMsgData;

}

class FirebaseSender;

class FirebaseGatewayManager : public QObject
{
    Q_OBJECT
public:
    using FirebaseResMsgData = firebase_utils::API_Usage::FirebaseResMsgData;

    ~FirebaseGatewayManager();
    static FirebaseGatewayManager& instance()
    {
        static FirebaseGatewayManager instance;
        return instance;
    }

public slots:
    void onPostRequestFinished(const FirebaseResMsgData &data);

signals:
    void initWrappers();
    void operate(const QJsonObject &payload);

private:
    FirebaseGatewayManager();

    void startConnection();
    void endConnection();

    QThread workerThread;
    FirebaseSender *m_sender;
};

#endif // FIREBASEGATEWAYMANAGER_H
