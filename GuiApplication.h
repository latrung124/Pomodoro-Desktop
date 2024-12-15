/*
* GuiApplication.h
* Author: Trung La
* Date: 2024-12-15
* This is a class for managing GUI application
*/

#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H

#include <QGuiApplication>

class GuiApplication
{
public:
    static void setInstance(QGuiApplication* _app);
    static QGuiApplication* getInstance();
};

#endif // GUIAPPLICATION_H