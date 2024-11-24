/*
* ServiceManager.cpp
* Author: Trung La
* Date: 2024-11-25
* This is a class for managing services
*/

#include "ServiceManager.h"
#include "IBaseService.h"

#include <iostream>

ServiceManager::~ServiceManager()
{
    disconnectAllServices();
}

void ServiceManager::disconnectAllServices()
{
    for (auto& service : m_services) {
        if (service.second) {
            service.second->disconnect();
        }
    }
    m_services.clear();
}

template <typename Service>
std::shared_ptr<Service> ServiceManager::registerService()
{
    auto service = std::make_shared<Service>();
    auto serviceId = typeid(Service).hash_code();

    if (m_services.find(serviceId) != m_services.end()) {
        throw std::runtime_error("Service already registered");
    }

    if (!service->connect()) {
        throw std::runtime_error("Failed to connect to service");
    }

    m_services[serviceId] = service;
    return std::dynamic_pointer_cast<Service>(service);
}

template <typename Service>
void ServiceManager::unregister()
{
    auto serviceId = typeid(Service).hash_code();
    auto it = m_services.find(serviceId);

    if (it == m_services.end()) {
        throw std::runtime_error("Service not found");
    }

    it->second->disconnect();
    m_services.erase(it);
}

template <typename Service>
std::shared_ptr<Service> ServiceManager::getService()
{
    auto serviceId = typeid(Service).hash_code();
    auto it = m_services.find(serviceId);

    if (it == m_services.end()) {
        throw std::runtime_error("Service not found");
    }

    return std::dynamic_pointer_cast<Service>(it->second);
}