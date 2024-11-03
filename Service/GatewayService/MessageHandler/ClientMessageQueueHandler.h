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

#include <queue>
#include <mutex>
#include <condition_variable>

class ClientMessageQueueHandler
{
public:
    static ClientMessageQueueHandler &getInstance();

    void enqueueMessage(const std::vector<uint8_t> &message);
    std::vector<uint8_t> dequeueMessage();

private:
    ClientMessageQueueHandler() = default;

    ClientMessageQueueHandler(const ClientMessageQueueHandler &) = delete;
    ClientMessageQueueHandler &operator=(const ClientMessageQueueHandler &) = delete;

    std::queue<std::vector<uint8_t>> m_messageQueue;
    std::mutex m_mutex;
    std::condition_variable m_condition;
};