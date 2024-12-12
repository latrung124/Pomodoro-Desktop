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
class FirebaseListenerManager;

class FirebaseGatewayManager : public QObject
{
    Q_OBJECT
public:
    using FirebaseResMsgData = firebase_utils::API_Usage::FirebaseResMsgData;

    FirebaseGatewayManager(QObject *parent = nullptr);
    ~FirebaseGatewayManager();

    void setFirebaseListenerManager(std::shared_ptr<FirebaseListenerManager> listenerManager);
    void init();

public slots:
    void onPostRequestFinished(const FirebaseResMsgData &data) const;

signals:
    void initWrappers();
    void operate(const QJsonObject &payload);

private:
    void startConnection();
    void endConnection();

    QThread workerThread;
    FirebaseSender *m_sender;
    std::weak_ptr<FirebaseListenerManager> m_listenerManager;
};

#endif // FIREBASEGATEWAYMANAGER_H
