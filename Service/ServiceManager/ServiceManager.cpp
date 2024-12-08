/*
* ServiceManager.cpp
* Author: Trung La
* Date: 2024-11-25
* This is a class for managing services
*/

#include "ServiceManager.h"
#include "IBaseService.h"

ServiceManager& ServiceManager::instance()
{
    static ServiceManager instance;
    return instance;
}

ServiceManager::~ServiceManager()
{
    disconnectAllServices();
}

void ServiceManager::disconnectAllServices()
{
    for (const auto& [serviceId, service] : m_services) {
        if (service) {
            service->disconnect();
        }
    }

    m_services.clear();
}