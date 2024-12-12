/*
* FirebaseRequestHelper.h
* Author: Trung La
* Date: 2024-12-01
* This is a helper class for handling Firebase requests
*/

#ifndef FIREBASEREQUESTHELPER_H
#define FIREBASEREQUESTHELPER_H

#include "Utils/CloudUtility/AuthenticationType.h"
#include "Utils/CloudUtility/FirebaseUtility.h"
#include "Core/Helper/Firebase/FirebaseHandlerHelper.h"
#include "Handler/Firebase/FirebaseRequestHandler.h"

#include <thread>

namespace helper {

namespace firebase {

using SignInData = Utils::Cloud::Firebase::SignInData;

void constructSignInRequest(const AuthenticationType &authType,
    const std::string &email, const std::string &password) {
    SignInData data{
        .authType = authType,
        .email = email,
        .password = password
    };

    // detach request to a new thread
    std::thread requestThread([data]() {
        // send request to Firebase
        auto firebaseRequestHandler = utils::firebase::getServiceHandler<FirebaseRequestHandler>();
        if (auto handler = firebaseRequestHandler.lock(); handler) {
            handler->enqueueMessage(Utils::Cloud::Firebase::MessageData{data});
        }
    });
    requestThread.detach();
}

} // namespace firebase

} // namespace helper

#endif // FIREBASEREQUESTHELPER_H
