/*
* FirebaseFactoryHelper.h
* Author: Trung La
* Date: 2024-12-01
* This class is a helper class for FirebaseFactory
*/

#ifndef FIREBASEFACTORYHELPER_H
#define FIREBASEFACTORYHELPER_H

#include "FirebaseUtils.h"

namespace firebase_helper {

namespace factory {

firebase_utils::gateway::FirebasePostRequest constructSignInRequest(const std::string &email, const std::string &password)
{
    using namespace firebase_utils::gateway;
    FirebasePostRequest request;
    request.url = "https://www.googleapis.com/identitytoolkit/v3/relyingparty/verifyPassword?key=";
    request.payload["email"] = QString::fromStdString(email);
    request.payload["password"] = QString::fromStdString(password);
    request.payload["returnSecureToken"] = true;

    return request;
}

} // namespace firebase_helper::factory

} // namespace firebase_helper

#endif // FIREBASEFACTORYHELPER_H