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

class FirebaseApp {
public:
    FirebaseApp();
    ~FirebaseApp();

    bool initialize();
    void exit();

    bool isInitialized() const;

    std::weak_ptr<FirebaseAuthentication> getAuth() const;

private:
    bool parseConfigJson(ProjectConfig& config);

    bool m_isInitialized;
    std::string m_configJsonStr;
    std::shared_ptr<FirebaseAuthentication> m_auth;
    ProjectConfig m_projectConfig;
};

#endif // FIREBASEAPP_H