/*
* FirebaseRequestProcessor.h
* Author: Trung La
* Date: 2024-11-25
* This class for processing Firebase requests
*/

#ifndef FIREBASEREQUESTPROCESSOR_H
#define FIREBASEREQUESTPROCESSOR_H

#include "Utils/CloudUtility/FirebaseUtility.h"

struct FirebaseRequestProcessor {
    void operator()(const Utils::Cloud::Firebase::SignInData& data);
    void operator()(const Utils::Cloud::Firebase::SignUpData& data) const;
    void operator()(const Utils::Cloud::Firebase::UpdatePasswordData& data) const;
    void operator()(const Utils::Cloud::Firebase::SignOutData& data) const;
    void operator()(const std::monostate&) const;
};

#endif // FIREBASEREQUESTPROCESSOR_H
