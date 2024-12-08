/*
* FirebaseListenerManager.h
* Author: Trung La
* Date: 2024-12-08
* This class is a manager class for Firebase listeners
*/

#ifndef FIREBASELISTENERMANAGER_H
#define FIREBASELISTENERMANAGER_H

#include <vector>

#include "Interface/IFirebaseAuthListener.h"

class FirebaseListenerManager
{
public:
    FirebaseListenerManager() = default;
    virtual ~FirebaseListenerManager() = default;

    void registerListener(IFirebaseAuthListenerPtr listener);
    void unregisterListener(IFirebaseAuthListenerPtr listener);

    template <typename ListenerType, typename... Args>
    void notifyListeners(Args&&... args) {
        for (const auto& listener : m_listeners) {
            if (auto castedListener = std::dynamic_pointer_cast<ListenerType>(listener); castedListener) {
                castedListener->onResponse(std::forward<Args>(args)...);
            }
        }
    }

private:
    std::vector<IFirebaseAuthListenerPtr> m_listeners;
};

#endif // FIREBASELISTENERMANAGER_H
