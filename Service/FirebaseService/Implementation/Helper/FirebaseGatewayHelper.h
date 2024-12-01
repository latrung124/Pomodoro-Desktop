/*
* FirebaseGatewayHelper.h
* Author: Trung La
* Date: 2024-12-01
* This class is a helper class for FirebaseGateway
*/

#ifndef FIREBASEGATEWAYHELPER_H
#define FIREBASEGATEWAYHELPER_H

#include "FirebaseUtils.h"
#include "FirebaseGateway/FirebaseGatewayManager.h"
#include "FirebaseGateway/FirebaseSender.h"

#include <type_traits>

namespace firebase_helper {

namespace gateway {

template <typename PostRequest>
void postRequest(const PostRequest &request)
{
    // Check type of request
    using FirebasePostRequest = firebase_utils::gateway::FirebasePostRequest;
    using PostRequestType = decltype(request);
    if constexpr (std::is_same_v<PostRequestType, FirebasePostRequest>) {
        static_assert(std::is_same<PostRequestType, FirebasePostRequest>::value, "FirebasePostRequest type is not as expected");
    }

    auto firebaseSender = FirebaseGatewayManager::instance().getFirebaseAuthSender().lock();
    if (firebaseSender) {
        firebaseSender->postRequest(request.url, request.payload);
    }
}

} // namespace firebase_helper::gateway

} // namespace firebase_helper

#endif // FIREBASEGATEWAYHELPER_H
