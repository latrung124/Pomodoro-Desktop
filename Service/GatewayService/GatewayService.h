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

#ifndef GATEWAYSERVICE_H_
#define GATEWAYSERVICE_H_

#include "interface/IGatewayService.h"

class GatewayService : public IGatewayService {
public:
    GatewayService() = default;
    virtual ~GatewayService() = default;

    void start() override;
    void stop() override;

    service_utils::ServiceId getServiceId() const override;

    std::shared_ptr<IGatewayServiceApiSender> getApiCaller() override;
    std::shared_ptr<IGatewayServiceApiReceiver> getApiReceiver() override;

private:
    void initialize();

    std::shared_ptr<IGatewayServiceApiSender> mApiCaller;
    std::shared_ptr<IGatewayServiceApiReceiver> mApiReceiver;

    service_utils::ServiceId mServiceId = service_utils::ServiceId::GATEWAY_SERVICE;
};

#endif // GATEWAYSERVICE_H_
