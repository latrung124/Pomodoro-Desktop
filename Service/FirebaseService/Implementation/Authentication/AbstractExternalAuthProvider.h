/*
* AbstractExternalAuthProvider.h
* Author: Trung La
* Date: 2024-11-24
* This is an abstract class for external authentication providers
*/

#ifndef ABSTRACTEXTERNALAUTHPROVIDER_H
#define ABSTRACTEXTERNALAUTHPROVIDER_H

#include <QObject>

class AbstractExternalAuthProvider : public QObject
{
    Q_OBJECT
public:
    AbstractExternalAuthProvider(QObject* parent = nullptr)
        : QObject(parent) {}
    virtual ~AbstractExternalAuthProvider() = default;

    AbstractExternalAuthProvider(const AbstractExternalAuthProvider&) = delete;
    AbstractExternalAuthProvider& operator=(const AbstractExternalAuthProvider&) = delete;
    AbstractExternalAuthProvider(AbstractExternalAuthProvider&&) = delete;
    AbstractExternalAuthProvider& operator=(AbstractExternalAuthProvider&&) = delete;

    virtual bool signIn() = 0;
};

#endif // ABSTRACTEXTERNALAUTHPROVIDER_H
