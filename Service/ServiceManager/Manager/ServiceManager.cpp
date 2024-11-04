/*
 * Copyright (C) 2024 La Trung
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file is part of a gateway library that use for transport
 * messages between client and server.
 *
 * Author: La Trung
 */

#include "ServiceManager.h"

void ServiceManager::start() {
}

void ServiceManager::stop() {
    for (auto &service : mServiceMap) {
        service.second->stop();
    }
}

service_utils::ServiceId ServiceManager::getServiceId() const {
    return service_utils::ServiceId::SERVICE_MANAGER;
}

void ServiceManager::registerService(std::shared_ptr<IService> service) {
    mServiceMap[service->getServiceId()] = service;
}

template <typename Service>
std::shared_ptr<Service> ServiceManager::getService(const service_utils::ServiceId &serviceId) const {
    auto it = mServiceMap.find(serviceId);
    if (it != mServiceMap.end()) {
        return std::dynamic_pointer_cast<Service>(it->second);
    }

    return nullptr;
}
