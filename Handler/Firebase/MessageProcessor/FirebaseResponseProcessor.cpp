/*
* FirebaseResponseProcessor.cpp
* Author: Trung La
* Date: 2024-12-06
* This class for processing Firebase responses
*/

#include "FirebaseResponseProcessor.h"
#include "Core/Manager/ControllerManager.h"
#include "Controller/SystemController.h"
#include "Controller/ModuleController/LoginModuleController.h"

void FirebaseResponseProcessor::operator()(const ExchangeCustomTokenResData& data) const
{
    printf("ExchangeCustomToken response\n");
}

void FirebaseResponseProcessor::operator()(const ExchangeRefreshTokenResData& data) const
{
    printf("ExchangeRefreshToken response\n");
}

void FirebaseResponseProcessor::operator()(const SignInEmailPasswordResData& data) const
{
    printf("SignInEmailPassword response\n");
    auto loginModuleController = ControllerManager::instance().getController<SystemController>()->getLoginModuleController().lock();
    if (!loginModuleController) {
        return;
    }

    if (auto userModel = loginModuleController->getUserModel().lock(); userModel) {
        if (data.email != "") {
            userModel->updateModel(data.email, true);
        } else {
            userModel->updateModel("", false);
        }
    }
}

void FirebaseResponseProcessor::operator()(const SignUpEmailPasswordResData& data) const
{
    printf("SignUpEmailPassword response\n");
}

void FirebaseResponseProcessor::operator()(const SignInAnounymousResData& data) const
{
    printf("SignInAnounymous response\n");
}

void FirebaseResponseProcessor::operator()(const ChangePasswordResData& data) const
{
    printf("ChangePassword response\n");
}

void FirebaseResponseProcessor::operator()(const SendPwResetEmailResData& data) const
{
    printf("SendPwResetEmail response\n");
}

void FirebaseResponseProcessor::operator()(const VerifyPwResetCodeResData& data) const
{
    printf("VerifyPwResetCode response\n");
}

void FirebaseResponseProcessor::operator()(const ConfirmPwResetResData& data) const
{
    printf("ConfirmPwReset response\n");
}

void FirebaseResponseProcessor::operator()(const ChangeEmailResData& data) const
{
    printf("ChangeEmail response\n");
}

void FirebaseResponseProcessor::operator()(const UpdateProfileResData& data) const
{
    printf("UpdateProfile response\n");
}

void FirebaseResponseProcessor::operator()(const GetUserDataResData& data) const
{
    printf("GetUserData response\n");
}

void FirebaseResponseProcessor::operator()(const GoogleAccessTokenResData& data) const
{
    printf("GetUserData response\n");
}
