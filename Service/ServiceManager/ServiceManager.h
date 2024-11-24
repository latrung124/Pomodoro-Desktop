/*
* ServiceManager.h
* Author: Trung La
* Date: 2024-11-25
* This is a class for managing services
*/

#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <memory>
#include <unordered_map>

class IBaseService;

class ServiceManager
{
public:
    ServiceManager() = default;
    ~ServiceManager();

    ServiceManager(const ServiceManager&) = delete;
    ServiceManager& operator=(const ServiceManager&) = delete;

    void disconnectAllServices();

    template <typename Service>
    std::shared_ptr<Service> registerService();

    template <typename Service>
    void unregister();

    template <typename Service>
    std::shared_ptr<Service> getService();

private:
    std::unordered_map<size_t, std::shared_ptr<IBaseService>> m_services;
};

#endif // SERVICEMANAGER_H