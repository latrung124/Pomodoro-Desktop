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

class FirebaseGatewayManager : public QObject
{
    Q_OBJECT
public:
    ~FirebaseGatewayManager();
    static FirebaseGatewayManager& instance()
    {
        static FirebaseGatewayManager instance;
        return instance;
    }

signals:
    void initWrappers();
    void operate(const QJsonObject &payload);

private:
    FirebaseGatewayManager();

    QThread workerThread;
};

#endif // FIREBASEGATEWAYMANAGER_H
