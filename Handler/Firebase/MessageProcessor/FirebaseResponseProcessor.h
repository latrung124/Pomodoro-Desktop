/*
* FirebaseResponseProcessor.h
* Author: Trung La
* Date: 2024-12-06
* This class for processing Firebase responses
*/

#ifndef FIREBASERESPONSEPROCESSOR_H
#define FIREBASERESPONSEPROCESSOR_H

#include "Service/FirebaseService/FirebaseUtils.h"

namespace {
    using namespace firebase_utils::API_Usage;
}

struct FirebaseResponseProcessor {
    void operator()(const ExchangeCustomTokenResData& data) const;
    void operator()(const ExchangeRefreshTokenResData& data) const;
    void operator()(const SignInEmailPasswordResData& data) const;
    void operator()(const SignUpEmailPasswordResData& data) const;
    void operator()(const SignInAnounymousResData& data) const;
    void operator()(const ChangePasswordResData& data) const;
    void operator()(const SendPwResetEmailResData& data) const;
    void operator()(const VerifyPwResetCodeResData& data) const;
    void operator()(const ConfirmPwResetResData& data) const;
    void operator()(const ChangeEmailResData& data) const;
    void operator()(const UpdateProfileResData& data) const;
    void operator()(const GetUserDataResData& data) const;
    void operator()(const GoogleAccessTokenResData& data) const;
};

#endif // FIREBASERESPONSEPROCESSOR_H
