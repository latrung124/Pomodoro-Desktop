/*
* FirebaseListenerManager.cpp
* Author: Trung La
* Date: 2024-12-08
* This class is a manager class for Firebase listeners
*/

#include "Implementation/FirebaseListenerManager.h"

#include <QDebug>

void FirebaseListenerManager::registerListener(IFirebaseAuthListenerPtr listener)
{
    qDebug() << "FirebaseListenerManager::registerListener!";
    m_listeners.push_back(listener);
}

void FirebaseListenerManager::unregisterListener(IFirebaseAuthListenerPtr listener)
{
    qDebug() << "FirebaseListenerManager::unregisterListener!";
    m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener), m_listeners.end());
}
