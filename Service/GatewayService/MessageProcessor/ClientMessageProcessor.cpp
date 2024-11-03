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

#include "ClientMessageProcessor.h"
#include "MessageHandler/ClientMessageQueueHandler.h"

namespace gateway::message_processor::client
{

void ClientMessageProcessor::processLoginRequest(const std::string &username,
                                                 const std::string &password,
                                                 const authentication::AuthChannel &authChannel)
{
    auto request = createLoginRequest(username, password, authChannel);
    // Send the request to the client msg queue handler

    ClientMessageQueueHandler::getInstance().enqueueMessage(request);
}

RequestMsgData ClientMessageProcessor::createLoginRequest(const std::string &username,
                                                          const std::string &password,
                                                          const authentication::AuthChannel &authChannel)
{
    authentication::LoginRequest request;
    request.set_username(username);
    request.set_password(password);
    request.set_auth_channel(authChannel);
    // Serialize the request to a byte array
    RequestMsgData msgData(request.ByteSizeLong());
    request.SerializeToArray(msgData.data(), msgData.size());
    return msgData;
}

} // namespace gateway::message_processor::client
