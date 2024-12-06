/*
* ServiceController.cpp
* Author: Trung La
* Date: 2024-11-25
* This is a class for managing services
*/

#include "ServiceController.h"

#include "Service/ServiceManager/ServiceManager.h"
#include "Handler/Firebase/FirebaseRequestHandler.h"
#include "Handler/Firebase/FirebaseResponseHandler.h"

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

    registerMessageHandlers();
}

void ServiceController::stop()
{
}

void ServiceController::registerMessageHandlers()
{
    if (m_firebaseService.expired()) {
        qWarning() << "Firebase service is not available";
        return;
    } else {
        if (auto firebaseService = m_firebaseService.lock(); firebaseService) {
            m_messageHandlers.push_back(std::make_shared<FirebaseRequestHandler>());
            m_messageHandlers.push_back(std::make_shared<FirebaseResponseHandler>());
        }
    }
}

std::weak_ptr<IFirebaseService> ServiceController::getFirebaseService() const
{
    return m_firebaseService;
}
