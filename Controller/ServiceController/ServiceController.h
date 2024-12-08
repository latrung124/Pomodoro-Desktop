/*
* ServiceController.h
* Author: Trung La
* Date: 2024-11-25
* This is a class for managing services
*/

#ifndef SERVICECONTROLLER_H
#define SERVICECONTROLLER_H

#include "Controller/BaseController.h"

#include <vector>
#include <memory>

class ServiceManager;
class IFirebaseService;
class AbstractMessageHandler;
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

    template <typename Handler>
    std::weak_ptr<Handler> getMessageHandler() const {
        for (const auto& handler : m_messageHandlers) {
            if (auto castedHandler = std::dynamic_pointer_cast<Handler>(handler); castedHandler) {
                return castedHandler;
            }
        }
        return {};
    }

private:
    void registerServices();
    void registerServiceListeners();
    void registerMessageHandlers();

    void registerFirebaseServiceListener();

    std::weak_ptr<IFirebaseService> m_firebaseService;
    std::shared_ptr<FirebaseRequestHandler> m_firebaseRequestHandler;
    std::vector<std::shared_ptr<AbstractMessageHandler>> m_messageHandlers;
};

#endif // SERVICECONTROLLER_H
