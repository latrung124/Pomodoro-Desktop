/*
* FirebaseResponseHandler.cpp
* Author: Trung La
* Date: 2024-12-06
* This is the implementation of the FirebaseResponseHandler class
*/

#include "FirebaseResponseHandler.h"
#include "Handler/Firebase/MessageProcessor/FirebaseResponseProcessor.h"

FirebaseResponseHandler::FirebaseResponseHandler()
{
    m_isRunning = false;
    m_processThread = std::thread([this] { processMessage(); });
}

FirebaseResponseHandler::~FirebaseResponseHandler()
{
    if (m_processThread.joinable()) {
        m_processThread.join();
    }
}

void FirebaseResponseHandler::processMessage()
{
    while (true) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition.wait(lock, [this] { return !m_messageQueue.empty(); });

        auto response = m_messageQueue.front();
        m_messageQueue.pop();
        lock.unlock();

        // Process response
        std::visit(FirebaseResponseProcessor{}, response.data);
    }
}
