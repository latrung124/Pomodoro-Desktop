/*
* GuiApplication.cpp
* Author: Trung La
* Date: 2024-12-15
* This is a class for managing GUI application
*/

#include "GuiApplication.h"

static QGuiApplication* app = nullptr;

void GuiApplication::setInstance(QGuiApplication* _app)
{
    app = _app;
}

QGuiApplication* GuiApplication::getInstance()
{
    return app;
}