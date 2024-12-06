/*
* FirebaseRequestHandler.cpp
* Author: Trung La
* Date: 2024-11-25
* This class for handling Firebase requests
*/

#include "FirebaseRequestHandler.h"
#include "Handler/Firebase/MessageProcessor/FirebaseRequestProcessor.h"

#include <QDebug>

FirebaseRequestHandler::FirebaseRequestHandler()
{
    m_isRunning = false;
    m_processThread = std::thread([this] { processMessage(); });
    qDebug() << "FirebaseRequestHandler created";
}

FirebaseRequestHandler::~FirebaseRequestHandler()
{
    if(m_processThread.joinable()) {
        m_processThread.join();
    }
}

void FirebaseRequestHandler::processMessage()
{
    while (true) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition.wait(lock, [this] { return !m_messageQueue.empty();});

        auto request = m_messageQueue.front();
        m_messageQueue.pop();
        lock.unlock();

        // Process request
        std::visit(FirebaseRequestProcessor{}, request.data);
    }
}
