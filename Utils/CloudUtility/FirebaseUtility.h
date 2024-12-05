/*
* FirebaseUtility.h
* Author: Trung La
* Date: 2024-11-25
* This is a utility class for Firebase
*/

#ifndef FIREBASEUTILITY_H
#define FIREBASEUTILITY_H

#include "Utils/CloudUtility/AuthenticationType.h"

#include <string>
#include <cstdint>
#include <variant>

#include <QHash>
#include <QString>

namespace Utils
{

namespace Cloud
{

namespace Firebase
{

struct SignInData {
    AuthenticationType authType;
    std::string email;
    std::string password;
};

struct SignUpData {
    std::string email;
    std::string password;
};

struct UpdatePasswordData {
    std::string newPassword;
};

struct SignOutData {
    std::monostate data;
};

struct MessageData {
    std::variant<SignInData, SignUpData, UpdatePasswordData, SignOutData, std::monostate> data;
};

} // namespace Utils::Cloud::Firebase

} // namespace Utils::Cloud

} // namespace Utils

#endif // FIREBASEUTILITY_H
