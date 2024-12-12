/*
* FirebaseAuthListenerImpl.h
* Author: Trung La
* Date: 2024-12-08
* This class is an interface for Firebase Auth listener
*/

#ifndef FIREBASEAUTHLISTENER_H
#define FIREBASEAUTHLISTENER_H

#include "Interface/IFirebaseAuthListener.h"

class FirebaseAuthListenerImpl : public IFirebaseAuthListener
{
public:
    FirebaseAuthListenerImpl() = default;
    virtual ~FirebaseAuthListenerImpl() = default;

    void setCallback(std::function<void(const std::any&)> callback) override;

    void onResponse(const firebase_utils::API_Usage::FirebaseResMsgData & data) override;

private:
    void notify(const std::any& wrappedData) {
        if (m_callback) {
            m_callback(wrappedData);
        }
    }

};
#endif // FIREBASEAUTHLISTENER_H