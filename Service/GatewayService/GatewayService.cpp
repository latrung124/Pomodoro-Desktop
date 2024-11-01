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

#include "GatewayService.h"
#include "GatewayServiceApiSender.h"

void GatewayService::start() {
    // Start the gateway service
    initialize();
}

void GatewayService::stop() {
    // Stop the gateway service
}

void GatewayService::initialize() {
    // Initialize the gateway service
    mApiCaller = std::make_shared<GatewayServiceApiSender>();
}