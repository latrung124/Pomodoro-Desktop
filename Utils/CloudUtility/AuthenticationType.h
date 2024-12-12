/*
* AuthenticationType.h
* Author: Trung La
* Date: 2024-11-29
* This is an enum class for authentication type
*/

#ifndef AUTHENTICATIONTYPE_H
#define AUTHENTICATIONTYPE_H

#include <QObject>

class AuthenticationTypeClass
{
    Q_GADGET
public:
    enum class EAuthenticationType : uint16_t
    {
        None = 0,
        EmailAndPassword,
        Google,
    };
    Q_ENUM(EAuthenticationType)

private:
    explicit AuthenticationTypeClass();
};

typedef AuthenticationTypeClass::EAuthenticationType AuthenticationType;

#endif // AUTHENTICATIONTYPE_H
