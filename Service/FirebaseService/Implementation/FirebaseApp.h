/*
* FirebaseApp.h
* Author: Trung La
* Date: 2024-11-24
* This is the implementation of the FirebaseApp class
*/

#ifndef FIREBASEAPP_H
#define FIREBASEAPP_H

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
    const std::string& getConfigJsonStr() const;

    std::weak_ptr<FirebaseAuthentication> getAuth() const;

private:
    bool m_isInitialized;
    std::string m_configJsonStr;
    std::shared_ptr<FirebaseAuthentication> m_auth;
};

#endif // FIREBASEAPP_H