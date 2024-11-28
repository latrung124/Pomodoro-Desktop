/*
* FirebaseUtility.h
* Author: Trung La
* Date: 2024-11-25
* This is a utility class for Firebase
*/

#ifndef FIREBASEUTILITY_H
#define FIREBASEUTILITY_H

#include <string>
#include <cstdint>
#include <variant>

namespace Utils
{

namespace Cloud
{

namespace Firebase
{

enum class AuthProviderType : uint16_t
{
    None = 0,
    EmailAndPassword,
    Google,
};

struct SignInData {
    AuthProviderType authType;
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
