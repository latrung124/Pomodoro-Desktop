/*
* IFirebaseAuthListener.h
* Author: Trung La
* Date: 2024-12-08
* This class is an interface for Firebase Auth listener
*/

#ifndef IFIREBASEAUTHLISTENER_H
#define IFIREBASEAUTHLISTENER_H

#include "IBaseServiceListener.h"

#include "FirebaseUtils.h"

class IFirebaseAuthListener : public IBaseServiceListener
{
public:
    IFirebaseAuthListener() = default;
    virtual ~IFirebaseAuthListener() = default;

    virtual void onResponse(const firebase_utils::API_Usage::FirebaseResMsgData & data) = 0;
};

using IFirebaseAuthListenerPtr = std::shared_ptr<IFirebaseAuthListener>;
#endif // IFIREBASEAUTHLISTENER_H
