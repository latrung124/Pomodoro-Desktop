/*
* FirebaseConfigHelper.h
* Author: Trung La
* Date: 2024-12-01
* This class is a helper class for FirebaseConfig
*/

#ifndef FIREBASECONFIGHELPER_H
#define FIREBASECONFIGHELPER_H

#include "FirebaseConfig.h"

namespace firebase_helper {

namespace config {

std::string getCurrentApiKey()
{
    return FirebaseConfig::instance().getProjectConfig().client.apiKey.current_key;
}

} // namespace firebase_helper::config

} // namespace firebase_helper

#endif // FIREBASECONFIGHELPER_H