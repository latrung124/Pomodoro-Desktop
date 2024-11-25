/*
* ServiceConcreteHelper.h
* Author: Trung La
* Date: 2024-11-25
* This is a helper class for concrete services
*/

#ifndef SERVICECONCRETEHELPER_H
#define SERVICECONCRETEHELPER_H

#include "FirebaseService/Implementation/FirebaseServiceImpl.h"

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
}

#endif // SERVICECONCRETEHELPER_H
