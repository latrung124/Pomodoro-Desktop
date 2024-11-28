/*
* ControllerHelper.h
* Author: Trung La
* Date: 2024-11-28
* This is a class for managing controllers
*/

#ifndef CONTROLLERS_CONTROLLERHELPER_H
#define CONTROLLERS_CONTROLLERHELPER_H

#include "Core/Manager/ControllerManager.h"

namespace helper {

template <typename ControllerType, typename... Args>
void addController(Args&&... args)
{
    ControllerManager::instance().addController<ControllerType>(std::forward<Args>(args)...);
}

template <typename ControllerType>
std::shared_ptr<ControllerType> getController()
{
    return ControllerManager::instance().getController<ControllerType>();
}

}

#endif // CONTROLLERS_CONTROLLERHELPER_H
