/*
* UserModel.h
* Author: Trung La
* Date: 2024-12-07
* This is the implementation of the UserModel class
*/

#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <mutex>

class UserModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(bool isAuthorized READ isAuthorized WRITE setIsAuthorized NOTIFY isAuthorizedChanged)
public:
    explicit UserModel(QObject *parent = nullptr);
    ~UserModel();

    void setEmail(const QString &email);
    QString email() const;

    void setIsAuthorized(bool isAuthorized);
    bool isAuthorized() const;

    void updateModel(const QString &email, bool isAuthorized);

signals:
    void emailChanged();
    void isAuthorizedChanged();

private:
    QString m_email;
    bool m_isAuthorized;
    mutable std::mutex m_mutex;
};

#endif // USERMODEL_H
