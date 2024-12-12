/*
* FirebaseHandlerHelper.h
* Author: Trung La
* Date: 2024-12-01
* This is a helper class for handling Firebase requests
*/

#ifndef FIREBASEHANDLERHELPER_H
#define FIREBASEHANDLERHELPER_H

#include "Core/Helper/ControllerHelper.h"
#include "Controller/ServiceController/ServiceController.h"

#include <memory>

namespace utils {

namespace firebase {

template <typename Handler>
std::weak_ptr<Handler> getServiceHandler()
{
    auto serviceController = helper::system::getController<ServiceController>();
    if (!serviceController) {
        return {};
    }
    return serviceController->getMessageHandler<Handler>();
}

} // namespace firebase

} // namespace utils

#endif // FIREBASEHANDLERHELPER_H