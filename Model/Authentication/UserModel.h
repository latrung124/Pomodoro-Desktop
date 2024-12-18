/*
* UserModel.h
* Author: Trung La
* Date: 2024-12-07
* This is the implementation of the UserModel class
*/

#ifndef USERMODEL_H
#define USERMODEL_H

#include "Utils/CloudUtility/AuthenticationType.h"

#include <QObject>
#include <mutex>

class UserModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AuthenticationType authenticationType READ authenticationType WRITE setAuthenticationType NOTIFY authenticationTypeChanged)
    Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName NOTIFY displayNameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(bool isAuthorized READ isAuthorized WRITE setIsAuthorized NOTIFY isAuthorizedChanged)
public:
    UserModel(QObject *parent = nullptr);
    ~UserModel();

    void update(const UserModel &userModel);

    void setAuthenticationType(AuthenticationType authenticationType);
    AuthenticationType authenticationType() const;

    void setDisplayName(const QString &displayName);
    QString displayName() const;

    void setEmail(const QString &email);
    QString email() const;

    void setPassword(const QString &password);
    QString password() const;

    void setIsAuthorized(bool isAuthorized);
    bool isAuthorized() const;

signals:
    void authenticationTypeChanged();
    void displayNameChanged();
    void emailChanged();
    void passwordChanged();
    void isAuthorizedChanged();

private:
    AuthenticationType m_authenticationType = AuthenticationType::None;
    QString m_displayName;
    QString m_email;
    QString m_password;
    bool m_isAuthorized = false;

    std::mutex m_mutex;
};
#endif // USERMODEL_H
