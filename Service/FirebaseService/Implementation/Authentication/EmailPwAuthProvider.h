/*
* EmailPwAuthProvider.h
* Author: Trung La
* Date: 2024-11-24
* This is an implementation class for Email/Password authentication provider
*/

#ifndef EMAILPWAUTHPROVIDER_H
#define EMAILPWAUTHPROVIDER_H

#include "Implementation/Authentication/AbstractInternalAuthProvider.h"

class EmailPwAuthProvider : public AbstractInternalAuthProvider
{
public:
    EmailPwAuthProvider() = default;
    virtual ~EmailPwAuthProvider() = default;

    bool signIn(const std::string &email, const std::string &password) override;
    bool deleteAccount() override;
    bool signUp(const std::string &email, const std::string &password) override;
    bool updatePassword(const std::string &newPassword) override;
};

#endif // EMAILPWAUTHPROVIDER_H