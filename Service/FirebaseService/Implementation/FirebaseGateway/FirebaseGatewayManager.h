/*
* FirebaseGatewayManager.h
* Author: Trung La
* Date: 2024-12-01
* This class is a manager class for FirebaseGateway
*/

#ifndef FIREBASEGATEWAYMANAGER_H
#define FIREBASEGATEWAYMANAGER_H

#include "FirebaseGateway/FirebaseSender.h"

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

    std::weak_ptr<FirebaseSender> getFirebaseAuthSender() const;

public slots:
    void onAuthRequestFinished(int statusCode, const QString &responseBody);
    void onAuthRequestError(const QString &error);

private:
    FirebaseGatewayManager(QObject *parent = nullptr);

    std::shared_ptr<FirebaseSender> m_authSender;
};

#endif // FIREBASEGATEWAYMANAGER_H
