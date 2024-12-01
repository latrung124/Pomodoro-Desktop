/*
* FirebaseHandlerHelper.h
* Author: Trung La
* Date: 2024-12-01
* This is a helper class for handling Firebase requests
*/

#ifndef FIREBASEHANDLERHELPER_H
#define FIREBASEHANDLERHELPER_H

#include "Core/Helper/ControllerHelper.h"
#include "Controller/ServiceController.h"

#include <memory>

namespace utils {

namespace firebase {

std::weak_ptr<FirebaseRequestHandler> getFirebaseRequestHandler()
{
    auto serviceController = helper::system::getController<ServiceController>();
    if (!serviceController) {
        return {};
    }
    return serviceController->getFirebaseRequestHandler();
}

} // namespace firebase

} // namespace utils

#endif // FIREBASEHANDLERHELPER_H