/*
* IBaseService.h
* Author: Trung La
* Date: 2024-11-25
* This is an interface class for BaseService
*/

#ifndef IBASESERVICE_H
#define IBASESERVICE_H

#include "IBaseServiceListener.h"
class IBaseService
{
public:
    IBaseService() = default;
    virtual ~IBaseService() = default;

    IBaseService(const IBaseService&) = delete;
    IBaseService& operator=(const IBaseService&) = delete;

    virtual bool connect() = 0; // call this function to connect to the service before using any other functions
    virtual void disconnect() = 0; // call this function to disconnect from the service

    virtual void registerListener(IBaseServiceListenerPtr listener) = 0;
    virtual void unregisterListener(IBaseServiceListenerPtr listener) = 0;
};

#endif // IBASESERVICE_H