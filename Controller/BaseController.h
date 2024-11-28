/*
* BaseController.h
* Author: Trung La
* Date: 2024-11-28
* This is a base class for all controllers
*/

#ifndef CONTROLLERS_BASECONTROLLER_H
#define CONTROLLERS_BASECONTROLLER_H

#include <QObject>

class BaseController : public QObject
{
    Q_OBJECT
public:
    BaseController(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~BaseController() = default;

    BaseController(const BaseController&) = delete;
    BaseController& operator=(const BaseController&) = delete;
};

#endif // CONTROLLERS_BASECONTROLLER_H