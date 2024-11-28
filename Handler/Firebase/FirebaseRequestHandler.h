/*
* FirebaseRequestHandler.h
* Author: Trung La
* Date: 2024-11-25
* This class for handling Firebase requests
*/

#ifndef FIREBASEREQUESTHANDLER_H
#define FIREBASEREQUESTHANDLER_H

#include "Utils/CloudUtility/FirebaseUtility.h"

#include <queue>
#include <mutex>
#include <condition_variable>

class FirebaseRequestHandler
{
public:
    using FirebaseMsgData = Utils::Cloud::Firebase::MessageData;
    FirebaseRequestHandler();
    ~FirebaseRequestHandler();

    template <typename Request>
    void enqueueRequest(Request&& request)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_requestQueue.push(std::forward<Request>(request));
        }
        m_condition.notify_one();
    }
private:
    void processRequest();

    bool m_isRunning;
    std::thread m_processThread;
    std::condition_variable m_condition;
    std::mutex m_mutex;
    std::queue<FirebaseMsgData> m_requestQueue;
};

#endif // FIREBASEREQUESTHANDLER_H
