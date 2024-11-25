/*
* ServiceManager.cpp
* Author: Trung La
* Date: 2024-11-25
* This is a class for managing services
*/

#include "ServiceManager.h"
#include "IBaseService.h"

#include <iostream>
#include <source_location>
#include <format>

namespace {

class ServiceException : public std::runtime_error
{
public:
    explicit ServiceException(const std::string& message, 
                            const std::source_location& location = std::source_location::current())
        : std::runtime_error(std::format(" Service error {} at {}:{}:{}",
        message, location.file_name(),
        location.line(), location.column()))
    {
    }
};

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

template<ServiceType Service>
[[nodiscard]] std::shared_ptr<Service> ServiceManager::registerService()
{
    auto service = std::make_shared<Service>();
    auto serviceId = typeid(Service).hash_code();

    if (const auto [it, inserted] = m_services.try_emplace({ serviceId, nullptr }); !inserted) {
        throw ServiceException(std::format("Service of type {} already registered", typeid(Service).name()));
    }

    try {
        if constexpr (requires { service->connect(); }) {
            if (!service->connect()) {
                throw ServiceException("Failed to connect to service");
            }
        } else {
            throw ServiceException("Service does not have connect function");
        }
    } catch (const std::exception& e) {
        m_services.erase(serviceId);
        throw ServiceException(e.what());
    }

    m_services[serviceId] = std::move(service);
    return std::static_pointer_cast<Service>(m_services[serviceId]);
}

template <ServiceType Service>
void ServiceManager::unregister()
{
    auto serviceId = typeid(Service).hash_code();
    if (const auto it = m_services.find(serviceId); it != m_services.end()) {
        m_services.erase(it);
    }

    throw ServiceException("Service not found");
}

template <ServiceType Service>
[[nodiscard]] std::shared_ptr<Service> ServiceManager::getService()
{
    auto serviceId = typeid(Service).hash_code();
    
    if (const auto it = m_services.find(serviceId); it != m_services.end()) {
        return std::static_pointer_cast<Service>(it->second);
    }

    throw ServiceException("Service not found");
}