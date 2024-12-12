/*
* FirebaseRequestHandler.h
* Author: Trung La
* Date: 2024-11-25
* This class for handling Firebase requests
*/

#ifndef FIREBASEREQUESTHANDLER_H
#define FIREBASEREQUESTHANDLER_H

#include "Utils/CloudUtility/FirebaseUtility.h"
#include "Handler/AbstractMessageHandler.h"

#include <mutex>
#include <queue>
#include <condition_variable>

class FirebaseRequestHandler : public AbstractMessageHandler
{
public:
    using FirebaseMsgData = Utils::Cloud::Firebase::MessageData;
    FirebaseRequestHandler();
    ~FirebaseRequestHandler();

    template <typename Data>
    void enqueueMessage(Data&& data)
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_messageQueue.push(std::forward<Data>(data));
        }
        m_condition.notify_one();
    }

private:
    void processMessage() override;

    std::queue<FirebaseMsgData> m_messageQueue;
    std::mutex m_mutex;
    std::condition_variable m_condition;
};

#endif // FIREBASEREQUESTHANDLER_H
