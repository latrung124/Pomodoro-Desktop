/*
* FirebaseHelper.h
* Author: Trung La
* Date: 2024-12-04
* This is the implementation of the FirebaseHelper class
*/

#ifndef FIREBASEHELPER_H
#define FIREBASEHELPER_H

#include "FirebaseConfig.h"
#include "FirebaseUtils.h"

namespace FirebaseGateway {

namespace Helper {

std::optional<ProjectConfig> getProjectConfig()
{
    return FirebaseConfig::instance().getProjectConfig();
}

std::string getCurrentApiKey() {
    auto projectConfig = FirebaseConfig::instance().getProjectConfig();
    if (!projectConfig.has_value()) {
        return "";
    }

    //currently we only have one client so we can return the first one
    if (projectConfig.value().clients.empty()) {
        return "";
    }

    return projectConfig.value().clients[0].apiKeys[0].current_key.toStdString();
}

QString getFirebaseApiPath(firebase_utils::API_Usage::FirebaseApi api)
{
    using namespace firebase_utils::API_Usage;
    auto path = gFirebaseApiPath.find(api);
    if (path == gFirebaseApiPath.end()) {
        return "";
    }

    return path.value();
}

} // namespace FirebaseGateway::Helper

} // namespace FirebaseGateway

#endif // FIREBASEHELPER_H