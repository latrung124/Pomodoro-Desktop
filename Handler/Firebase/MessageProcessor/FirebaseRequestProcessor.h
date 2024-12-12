/*
* FirebaseRequestProcessor.h
* Author: Trung La
* Date: 2024-11-25
* This class for processing Firebase requests
*/

#ifndef FIREBASEREQUESTPROCESSOR_H
#define FIREBASEREQUESTPROCESSOR_H

#include "Utils/CloudUtility/FirebaseUtility.h"

namespace {
    using namespace Utils::Cloud::Firebase;
}

struct FirebaseRequestProcessor {
    void operator()(const SignInData& data);
    void operator()(const SignUpData& data) const;
    void operator()(const UpdatePasswordData& data) const;
    void operator()(const SignOutData& data) const;
    void operator()(const std::monostate&) const;
};

#endif // FIREBASEREQUESTPROCESSOR_H
