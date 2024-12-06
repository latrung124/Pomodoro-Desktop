/*
* FirebaseResponseHandler.h
* Author: Trung La
* Date: 2024-12-06
* This is the implementation of the FirebaseResponseHandler class
*/

#ifndef FIREBASERESPONSEHANDLER_H
#define FIREBASERESPONSEHANDLER_H

#include "Service/FirebaseService/FirebaseUtils.h"
#include "Handler/AbstractMessageHandler.h"

#include <mutex>
#include <queue>
#include <condition_variable>

class FirebaseResponseHandler : public AbstractMessageHandler
{
public:
    using FirebaseResMsgData = firebase_utils::API_Usage::FirebaseResMsgData;

    FirebaseResponseHandler();
    ~FirebaseResponseHandler();

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

    std::queue<FirebaseResMsgData> m_messageQueue;
    std::mutex m_mutex;
    std::condition_variable m_condition;
};

#endif // FIREBASERESPONSEHANDLER_H
