/*
* ServiceController.h
* Author: Trung La
* Date: 2024-11-25
* This is a class for managing services
*/

#ifndef SERVICECONTROLLER_H
#define SERVICECONTROLLER_H

#include <memory>

class ServiceManager;
class IFirebaseService;

class ServiceController
{
public:
    ServiceController();
    ~ServiceController();

    ServiceController(const ServiceController&) = delete;
    ServiceController& operator=(const ServiceController&) = delete;

    void start();
    void stop();

private:
    std::weak_ptr<IFirebaseService> m_firebaseService;
};

#endif // SERVICECONTROLLER_H