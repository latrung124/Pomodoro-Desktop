/*
* ServiceManager.h
* Author: Trung La
* Date: 2024-11-25
* This is a class for managing services
*/

#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include "ServiceConcreteHelper.h"

#include <memory>
#include <unordered_map>
#include <format>
#include <source_location>

class IBaseService;

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

class ServiceManager
{
public:
    static ServiceManager& instance();
    ~ServiceManager();

    ServiceManager(const ServiceManager&) = delete;
    ServiceManager& operator=(const ServiceManager&) = delete;

    void disconnectAllServices();

    template<ServiceConcreteHelper::IServiceType IService>
    [[nodiscard]] std::shared_ptr<IService> registerService()
    {
        auto service = ServiceConcreteHelper::createConcreteService<IService>();
        auto serviceId = typeid(IService).hash_code();

        if (m_services.find(serviceId) != m_services.end()) {
            throw ServiceException("Service already registered");
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
        return std::static_pointer_cast<IService>(m_services[serviceId]);
    }

    template <ServiceConcreteHelper::IServiceType IService>
    void unregister()
    {
        auto serviceId = typeid(IService).hash_code();
        if (const auto it = m_services.find(serviceId); it != m_services.end()) {
            m_services.erase(it);
        }

        throw ServiceException("Service not found");
    }

    template <ServiceConcreteHelper::IServiceType IService>
    [[nodiscard]] std::shared_ptr<IService> getService()
    {
        auto serviceId = typeid(IService).hash_code();

        if (const auto it = m_services.find(serviceId); it != m_services.end()) {
            return std::static_pointer_cast<IService>(it->second);
        }

        throw ServiceException("Service not found");
    }

private:
    ServiceManager() = default;
    std::unordered_map<size_t, std::shared_ptr<IBaseService>> m_services;
};

#endif // SERVICEMANAGER_H
