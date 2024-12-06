/*
* AbstractMessageHandler.h
* Author: Trung La
* Date: 2024-12-06
* This is the abstract class for handling messages
*/

#ifndef ABSTRACTMESSAGEHANDLER_H
#define ABSTRACTMESSAGEHANDLER_H

#include <thread>

class AbstractMessageHandler
{
public:
    AbstractMessageHandler() = default;
    virtual ~AbstractMessageHandler() = default;

protected:
    virtual void processMessage() = 0;

    bool m_isRunning;
    std::thread m_processThread;
};

#endif // ABSTRACTMESSAGEHANDLER_H
