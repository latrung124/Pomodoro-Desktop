/*
* FirebaseRequestProcessor.cpp
* Author: Trung La
* Date: 2024-11-25
* This class for processing Firebase requests
*/

#include "FirebaseRequestProcessor.h"
#include "Core/Helper/ControllerHelper.h"
#include "Controller/ServiceController/ServiceController.h"
#include "Service/FirebaseService/Interface/IFirebaseService.h"

void FirebaseRequestProcessor::operator()(const SignInData& data)
{
    printf("SignIn request for user %s\n", data.email.c_str());
    if (auto firebaseService = helper::system::getController<ServiceController>()->getFirebaseService().lock(); firebaseService) {
        firebaseService->signIn(static_cast<AuthProviderType>(data.authType), data.email, data.password);
    }
}

void FirebaseRequestProcessor::operator()(const SignUpData& data) const
{
    printf("CreateAccount request for user %s\n", data.email.c_str());
    if (auto firebaseService =  helper::system::getController<ServiceController>()->getFirebaseService().lock(); firebaseService) {
        firebaseService->signUp(data.email, data.password);
    }
}

void FirebaseRequestProcessor::operator()(const UpdatePasswordData& data) const
{
    printf("UpdatePassword request\n");
    if(auto firebaseService =  helper::system::getController<ServiceController>()->getFirebaseService().lock(); firebaseService) {
        firebaseService->updatePassword(data.idToken, data.newPassword);
    }
}

void FirebaseRequestProcessor::operator()(const SignOutData& data) const
{
    printf("SignOut request\n");
    if(auto firebaseService =  helper::system::getController<ServiceController>()->getFirebaseService().lock(); firebaseService) {
        firebaseService->signOut();
    }
}

void FirebaseRequestProcessor::operator()(const std::monostate&) const
{
    printf("SignOut request\n");
    if(auto firebaseService =  helper::system::getController<ServiceController>()->getFirebaseService().lock(); firebaseService) {
        firebaseService->signOut();
    }
}
