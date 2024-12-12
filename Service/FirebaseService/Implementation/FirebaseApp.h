/*
* FirebaseApp.h
* Author: Trung La
* Date: 2024-11-24
* This is the implementation of the FirebaseApp class
*/

#ifndef FIREBASEAPP_H
#define FIREBASEAPP_H

#include "FirebaseUtils.h"

#include <string>
#include <memory>

class FirebaseAuthentication;
class FirebaseListenerManager;
class FirebaseGatewayManager;

class FirebaseApp {
public:
    FirebaseApp();
    ~FirebaseApp();

    bool initialize();
    void exit();

    bool isInitialized() const;

    std::weak_ptr<FirebaseAuthentication> getAuth() const;
    std::weak_ptr<FirebaseListenerManager> getListenerManager() const;

private:
    bool parseConfigJson(ProjectConfig& config);

    bool m_isInitialized;
    std::string m_configJsonStr;
    std::shared_ptr<FirebaseAuthentication> m_auth;
    ProjectConfig m_projectConfig;
    std::shared_ptr<FirebaseListenerManager> m_listenerManager;
    std::shared_ptr<FirebaseGatewayManager> m_gatewayManager;
};

#endif // FIREBASEAPP_H