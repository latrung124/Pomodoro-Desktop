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

#include "GatewayServiceApiSender.h"
#include "MessageProcessor/ClientMessageProcessor.h"

GatewayServiceApiSender::GatewayServiceApiSender()
    : m_clientMessageProcessor(std::make_unique<client_processor>())
{
}

GatewayServiceApiSender::GatewayServiceApiSender(GatewayServiceApiSender &&other) noexcept
    : m_clientMessageProcessor(std::move(other.m_clientMessageProcessor))
{
}

GatewayServiceApiSender &GatewayServiceApiSender::operator=(GatewayServiceApiSender &&other) noexcept
{
    if (this != &other) {
        m_clientMessageProcessor = std::move(other.m_clientMessageProcessor);
    }

    return *this;
}

void GatewayServiceApiSender::sendMessage(std::string)
{
    // Send message to the server
}

void GatewayServiceApiSender::requestLoginWithGoogle(std::string username, std::string password)
{
    using client_processor =  gateway::message_processor::client::ClientMessageProcessor;
        // Send login request to the server
        m_clientMessageProcessor->processLoginRequest(
            username, password, authentication::AuthChannel::GOOGLE);
}

void GatewayServiceApiSender::requestLoginWithFacebook(std::string username, std::string password)
{
    // Send login request to the server
    m_clientMessageProcessor->processLoginRequest(username, password, authentication::AuthChannel::FACEBOOK);
}
