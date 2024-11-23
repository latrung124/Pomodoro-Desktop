/*
* FirebaseApp.h
* Author: Trung La
* Date: 2024-11-24
* This is the implementation of the FirebaseApp class
*/

#ifndef FIREBASEAPP_H
#define FIREBASEAPP_H

#include <firebase/app.h>

class FirebaseApp {
public:
    FirebaseApp();
    ~FirebaseApp();

    bool initialize();
    void exit();

    firebase::App* getApp();

private:
    firebase::App* m_app;
    firebase::AppOptions* m_options;
};

#endif // FIREBASEAPP_H