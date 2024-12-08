/*
* ServiceController.cpp
* Author: Trung La
* Date: 2024-11-25
* This is a class for managing services
*/

#include "ServiceController.h"

#include "Service/ServiceManager/ServiceManager.h"
#include "Service/FirebaseService/Interface/IFirebaseAuthListener.h"
#include "Service/FirebaseService/Interface/IFirebaseService.h"
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
    registerServices();

    // Need register handler before register listener;
    registerMessageHandlers();

    registerServiceListeners();
}

void ServiceController::stop()
{
}

void ServiceController::registerServices()
{
    auto firebaseService = ServiceManager::instance().registerService<IFirebaseService>();
    m_firebaseService = firebaseService;
}

void ServiceController::registerServiceListeners()
{
    registerFirebaseServiceListener();
}

void ServiceController::registerFirebaseServiceListener()
{
    if (m_firebaseService.expired()) {
        qWarning() << "Firebase service is not available";
        return;
    } else {
        if (auto firebaseService = m_firebaseService.lock(); firebaseService) {
            auto firebaseAuthListener = ServiceManager::instance().registerListener<IFirebaseAuthListener>();
            firebaseAuthListener->setCallback([this](const std::any& data) {
                if (auto handler = getMessageHandler<FirebaseResponseHandler>().lock(); handler) {
                    handler->enqueueMessage(std::any_cast<FirebaseResponseHandler::FirebaseResMsgData>(data));
                }
            });
            firebaseService->registerListener(std::move(firebaseAuthListener));
        }
    }
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
