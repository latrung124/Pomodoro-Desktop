/*
* ServiceConcreteHelper.h
* Author: Trung La
* Date: 2024-11-25
* This is a helper class for concrete services
*/

#ifndef SERVICECONCRETEHELPER_H
#define SERVICECONCRETEHELPER_H

#include "FirebaseService/Implementation/FirebaseServiceImpl.h"
#include "FirebaseService/Implementation/Listener/FirebaseAuthListenerImpl.h"

#include <memory>

#include <concepts>

namespace ServiceConcreteHelper
{
    template<typename IService>
    concept IServiceType = std::derived_from<IService, IBaseService>;

    template<IServiceType IService>
    requires IServiceType<IService>
    std::shared_ptr<IService> createConcreteService()
    {
        if constexpr (std::same_as<IService, IFirebaseService>) {
            return std::make_shared<FirebaseServiceImpl>();
        }
        else {
            static_assert(false, "Service not implemented");
        }
    }

    template<typename IServiceListener>
    concept IServiceListenerType = std::derived_from<IServiceListener, IBaseServiceListener>;

    template<IServiceListenerType IServiceListener>
    requires IServiceListenerType<IServiceListener>
    std::shared_ptr<IServiceListener> concreteServiceListener()
    {
        if constexpr (std::same_as<IServiceListener, IFirebaseAuthListener>) {
            return std::make_shared<FirebaseAuthListenerImpl>();
        } else {
            static_assert(false, "Service listener not implemented");
        }
    }
}

#endif // SERVICECONCRETEHELPER_H
