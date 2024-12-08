/*
* FirebaseAuthListenerImpl.cpp
* Author: Trung La
* Date: 2024-12-08
* This class is an interface for Firebase Auth listener
*/

#include "Implementation/Listener/FirebaseAuthListenerImpl.h"
#include "FirebaseUtils.h"

void FirebaseAuthListenerImpl::setCallback(std::function<void(const std::any&)> callback)
{
    m_callback = std::move(callback);
}

void FirebaseAuthListenerImpl::onResponse(const firebase_utils::API_Usage::FirebaseResMsgData & data)
{
    // Process response
    printf("FirebaseAuthListenerImpl::onResponse() called\n");
    notify(std::any(data));
}
