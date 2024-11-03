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

#include "ClientMessageQueueHandler.h"

ClientMessageQueueHandler &ClientMessageQueueHandler::getInstance()
{
    static ClientMessageQueueHandler instance;
    return instance;
}

void ClientMessageQueueHandler::enqueueMessage(const std::vector<uint8_t> &message)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_messageQueue.push(message);
    m_condition.notify_one();
}

std::vector<uint8_t> ClientMessageQueueHandler::dequeueMessage()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_condition.wait(lock, [this] { return !m_messageQueue.empty(); });

    std::vector<uint8_t> message = m_messageQueue.front();
    m_messageQueue.pop();
    return message;
}