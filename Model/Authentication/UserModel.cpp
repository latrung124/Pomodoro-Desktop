/*
* UserModel.cpp
* Author: Trung La
* Date: 2024-12-07
* This is the implementation of the UserModel class
*/

#include "UserModel.h"
#include <QDebug>

UserModel::UserModel(QObject *parent)
    : QObject(parent)
    , m_isAuthorized(false)
{
}

UserModel::~UserModel()
{
}

void UserModel::update(const UserModel &userModel)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    setAuthenticationType(userModel.authenticationType());
    setDisplayName(userModel.displayName());
    setEmail(userModel.email());
    setPassword(userModel.password());
    setIsAuthorized(userModel.isAuthorized());
}

void UserModel::setAuthenticationType(AuthenticationType authenticationType)
{
    if (m_authenticationType == authenticationType) {
        return;
    }

    m_authenticationType = authenticationType;
    emit authenticationTypeChanged();
}

AuthenticationType UserModel::authenticationType() const
{
    return m_authenticationType;
}

void UserModel::setDisplayName(const QString &displayName)
{
    if (m_displayName == displayName) {
        return;
    }

    m_displayName = displayName;
    emit displayNameChanged();
}

QString UserModel::displayName() const
{
    return m_displayName;
}

void UserModel::setEmail(const QString &email)
{
    if (m_email == email) {
        return;
    }

    m_email = email;
    emit emailChanged();
}

QString UserModel::email() const
{
    return m_email;
}

void UserModel::setPassword(const QString &password)
{
    if (m_password == password) {
        return;
    }

    m_password = password;
    emit passwordChanged();
}

QString UserModel::password() const
{
    return m_password;
}

void UserModel::setIsAuthorized(bool isAuthorized)
{
    if (m_isAuthorized == isAuthorized) {
        return;
    }

    m_isAuthorized = isAuthorized;
    emit isAuthorizedChanged();
}

bool UserModel::isAuthorized() const
{
    return m_isAuthorized;
}
