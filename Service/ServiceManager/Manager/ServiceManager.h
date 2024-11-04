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

#pragma once

#include <map>

#include "IServiceManager.h"

class ServiceManager : public IServiceManager
{
public:
    ServiceManager() = default;
    virtual ~ServiceManager() = default;

    void start() override;
    void stop() override;

    service_utils::ServiceId getServiceId() const override;
    void registerService(std::shared_ptr<IService> service) override;
    template <typename Service>
    std::shared_ptr<Service> getService(const service_utils::ServiceId &serviceId) const;

private:
    std::map<service_utils::ServiceId, std::shared_ptr<IService>> mServiceMap;
};
