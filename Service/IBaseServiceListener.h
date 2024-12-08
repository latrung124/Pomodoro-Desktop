/*
* IBaseServiceListener.h
* Author: Trung La
* Date: 2024-12-08
* This is an interface class for BaseServiceListener
*/

#ifndef IBASESERVICELISTENER_H
#define IBASESERVICELISTENER_H

#include <memory>
#include <functional>
#include <any>

class IBaseServiceListener
{
public:
    IBaseServiceListener() = default;
    virtual ~IBaseServiceListener() = default;

    IBaseServiceListener(const IBaseServiceListener&) = delete;
    IBaseServiceListener& operator=(const IBaseServiceListener&) = delete;

    virtual void setCallback(std::function<void(const std::any&)> callback) = 0;

protected:
    std::function<void(const std::any&)> m_callback;
};

using IBaseServiceListenerPtr = std::shared_ptr<IBaseServiceListener>;

#endif // IBASESERVICELISTENER_H
