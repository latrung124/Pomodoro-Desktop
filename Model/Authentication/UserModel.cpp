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
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_email;
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
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_isAuthorized;
}

void UserModel::updateModel(const QString &email, bool isAuthorized)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    setEmail(email);
    setIsAuthorized(isAuthorized);
}
