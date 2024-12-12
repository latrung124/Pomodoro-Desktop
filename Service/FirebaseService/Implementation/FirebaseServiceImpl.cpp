/*
* FirebaseServiceImpl.cpp
* Author: Trung La
* Date: 2024-11-22
* This is an implementation class for FirebaseService
*/

#include "FirebaseServiceImpl.h"
#include "FirebaseApp.h"
#include "Implementation/Authentication/FirebaseAuthentication.h"
#include "Interface/IFirebaseAuthListener.h"
#include "FirebaseListenerManager.h"

#include <QDebug>

FirebaseServiceImpl::FirebaseServiceImpl()
    : m_isConnected(false),
    m_firebaseApp(std::make_unique<FirebaseApp>())
{
}

FirebaseServiceImpl::~FirebaseServiceImpl()
{
}

bool FirebaseServiceImpl::connect()
{
    return true;
}

void FirebaseServiceImpl::disconnect()
{
}

bool FirebaseServiceImpl::signIn(AuthProviderType authType, const std::string &email, const std::string &password)
{
    if (m_firebaseApp->isInitialized())
    {
        qDebug() << Q_FUNC_INFO << " FirebaseApp is initialized";
    }
    else
    {
        qWarning() << Q_FUNC_INFO << " FirebaseApp is not initialized";
        return false;
    }

    qDebug() << "FirebaseServiceImpl::signIn() called: " << email.c_str() << " " << password.c_str();
    if (auto auth = m_firebaseApp->getAuth().lock(); auth)
    {
        return auth->signIn(authType, email, password);
    } else {
        qWarning() << "Failed to get FirebaseAuthentication";
    }

    return false;
}

bool FirebaseServiceImpl::signOut()
{
    return false;
}

bool FirebaseServiceImpl::signUp(const std::string &email, const std::string &password)
{
    if (m_firebaseApp->isInitialized())
    {
        qDebug() << Q_FUNC_INFO << " FirebaseApp is initialized";
    }
    else
    {
        qWarning() << Q_FUNC_INFO << " FirebaseApp is not initialized";
        return false;
    }
    qDebug() << "FirebaseServiceImpl::signUp() called: " << email.c_str() << " " << password.c_str();
    if (auto auth = m_firebaseApp->getAuth().lock(); auth)
    {
        return auth->signUp(email, password);
    } else {
        qWarning() << "Failed to get FirebaseAuthentication";
    }

    return false;
}

bool FirebaseServiceImpl::deleteAccount()
{
    return false;
}

bool FirebaseServiceImpl::updatePassword(const std::string &idToken, const std::string &newPassword)
{
    if (m_firebaseApp->isInitialized())
    {
        qDebug() << Q_FUNC_INFO << " FirebaseApp is initialized";
    }
    else
    {
        qWarning() << Q_FUNC_INFO << " FirebaseApp is not initialized";
        return false;
    }
    qDebug() << "FirebaseServiceImpl::updatePassword() called: " << newPassword.c_str();
    if (auto auth = m_firebaseApp->getAuth().lock(); auth)
    {
        return auth->updatePassword(idToken, newPassword);
    } else {
        qWarning() << "Failed to get FirebaseAuthentication";
    }

    return false;
}

void FirebaseServiceImpl::registerListener(IBaseServiceListenerPtr listener)
{
    auto listenerManager = m_firebaseApp->getListenerManager().lock();
    if (listenerManager)
    {
        listenerManager->registerListener(dynamic_pointer_cast<IFirebaseAuthListener>(listener));
    }
    else
    {
        qWarning() << "Failed to get FirebaseListenerManager";
    }
}

void FirebaseServiceImpl::unregisterListener(IBaseServiceListenerPtr listener)
{
    auto listenerManager = m_firebaseApp->getListenerManager().lock();
    if (listenerManager)
    {
        listenerManager->unregisterListener(dynamic_pointer_cast<IFirebaseAuthListener>(listener));
    }
    else
    {
        qWarning() << "Failed to get FirebaseListenerManager";
    }
}
