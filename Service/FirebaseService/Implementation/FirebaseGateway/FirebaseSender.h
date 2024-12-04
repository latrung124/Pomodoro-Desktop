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

class FirebaseSender : public QObject
{
    Q_OBJECT
public:
    explicit FirebaseSender(QObject *parent = nullptr);
    ~FirebaseSender();

    void postRequest(const QJsonObject &payload);

public slots:
    void onInitWrapper();

private:
    std::unique_ptr<AuthWrapper> m_authWrapper;
};

#endif // FIREBASESENDER_H
