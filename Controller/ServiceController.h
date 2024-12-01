/*
* ServiceController.h
* Author: Trung La
* Date: 2024-11-25
* This is a class for managing services
*/

#ifndef SERVICECONTROLLER_H
#define SERVICECONTROLLER_H

#include "BaseController.h"

#include <memory>

class ServiceManager;
class IFirebaseService;
class FirebaseRequestHandler;

class ServiceController : public BaseController
{
    Q_OBJECT
public:
    ServiceController(QObject* parent = nullptr);
    ~ServiceController();

    ServiceController(const ServiceController&) = delete;
    ServiceController& operator=(const ServiceController&) = delete;

    void start();
    void stop();

    std::weak_ptr<IFirebaseService> getFirebaseService() const;
    std::weak_ptr<FirebaseRequestHandler> getFirebaseRequestHandler() const;

private:
    std::weak_ptr<IFirebaseService> m_firebaseService;
    std::shared_ptr<FirebaseRequestHandler> m_firebaseRequestHandler;
};

#endif // SERVICECONTROLLER_H