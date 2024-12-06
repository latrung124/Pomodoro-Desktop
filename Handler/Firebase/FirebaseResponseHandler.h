/*
* FirebaseResponseHandler.h
* Author: Trung La
* Date: 2024-12-06
* This is the implementation of the FirebaseResponseHandler class
*/

#ifndef FIREBASERESPONSEHANDLER_H
#define FIREBASERESPONSEHANDLER_H

#include "Service/FirebaseService/FirebaseUtils.h"

#include <queue>
#include <mutex>
#include <condition_variable>

class FirebaseResponseHandler
{
public:
    using FirebaseResMsgData = firebase_utils::API_Usage::FirebaseResMsgData;

    FirebaseResponseHandler();
    ~FirebaseResponseHandler();

    template <typename Response>
    void enqueueResponse(Response&& response)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_responseQueue.push(std::forward<Response>(response));
        }
        m_condition.notify_one();
    }

private:
    void processResponse();

    bool m_isRunning;
    std::thread m_processThread;
    std::condition_variable m_condition;
    std::mutex m_mutex;
    std::queue<FirebaseResMsgData> m_responseQueue;
};

#endif // FIREBASERESPONSEHANDLER_H