/*
* FirebaseRequestProcessor.cpp
* Author: Trung La
* Date: 2024-11-25
* This class for processing Firebase requests
*/

#include "FirebaseRequestProcessor.h"

void FirebaseRequestProcessor::operator()(const Utils::Cloud::Firebase::SignInData& data)
{
    printf("SignIn request for user %s\n", data.email.c_str());
}

void FirebaseRequestProcessor::operator()(const Utils::Cloud::Firebase::SignUpData& data) const
{
    printf("CreateAccount request for user %s\n", data.email.c_str());
}

void FirebaseRequestProcessor::operator()(const Utils::Cloud::Firebase::UpdatePasswordData& data) const
{
    printf("UpdatePassword request\n");
}

void FirebaseRequestProcessor::operator()(const Utils::Cloud::Firebase::SignOutData& data) const
{
    printf("SignOut request\n");
}

void FirebaseRequestProcessor::operator()(const std::monostate&) const
{
    printf("SignOut request\n");
}