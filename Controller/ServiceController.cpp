/*
* ServiceController.cpp
* Author: Trung La
* Date: 2024-11-25
* This is a class for managing services
*/

#include "ServiceController.h"

#include "Service/ServiceManager/ServiceManager.h"

ServiceController::ServiceController()
{
}

ServiceController::~ServiceController()
{
}

void ServiceController::start()
{
    auto firebaseService = ServiceManager::instance().registerService<IFirebaseService>();
    m_firebaseService = firebaseService;
}

void ServiceController::stop()
{
}
