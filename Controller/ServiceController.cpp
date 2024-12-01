/*
* ServiceController.cpp
* Author: Trung La
* Date: 2024-11-25
* This is a class for managing services
*/

#include "ServiceController.h"

#include "Service/ServiceManager/ServiceManager.h"
#include "Handler/Firebase/FirebaseRequestHandler.h"

#include <QDebug>

ServiceController::ServiceController(QObject* parent)
    : BaseController(parent)
{
}

ServiceController::~ServiceController()
{
}

void ServiceController::start()
{
    auto firebaseService = ServiceManager::instance().registerService<IFirebaseService>();
    m_firebaseService = firebaseService;

    if (m_firebaseService.expired()) {
        qWarning() << "Failed to register Firebase service";
    } else {
        qInfo() << "Firebase service registered";
        m_firebaseRequestHandler = std::make_shared<FirebaseRequestHandler>();
    }

}

void ServiceController::stop()
{
}

std::weak_ptr<IFirebaseService> ServiceController::getFirebaseService() const
{
    return m_firebaseService;
}

std::weak_ptr<FirebaseRequestHandler> ServiceController::getFirebaseRequestHandler() const
{
    return m_firebaseRequestHandler;
}
