/*
* ControllerManager.h
* Author: Trung La
* Date: 2024-11-28
* This is a class for managing controllers
*/

#ifndef CONTROLLERS_CONTROLLERMANAGER_H
#define CONTROLLERS_CONTROLLERMANAGER_H

#include <vector>
#include <memory>

class BaseController;

class ControllerManager
{
public:
    ControllerManager();
    ~ControllerManager();

    static ControllerManager& instance()
    {
        static ControllerManager instance;
        return instance;
    }

    ControllerManager(const ControllerManager&) = delete;
    ControllerManager& operator=(const ControllerManager&) = delete;

    template <typename ControllerType, typename... Args>
    void addController(Args&&... args)
    {
        for (const auto& controller : m_controllers) {
            if (auto castedController = std::dynamic_pointer_cast<ControllerType>(controller)) {
                return;
            }
        }
        m_controllers.push_back(std::make_shared<ControllerType>(std::forward<Args>(args)...));
    }

    template <typename ControllerType>
    std::shared_ptr<ControllerType> getController()
    {
        for (const auto& controller : m_controllers) {
            if (auto castedController = std::dynamic_pointer_cast<ControllerType>(controller)) {
                return castedController;
            }
        }
        return nullptr;
    }

    template <typename ControllerType>
    void removeController()
    {
        for (auto it = m_controllers.begin(); it != m_controllers.end(); ++it) {
            if (auto castedController = std::dynamic_pointer_cast<ControllerType>(*it)) {
                m_controllers.erase(it);
                return;
            }
        }
    }

private:
    std::vector<std::shared_ptr<BaseController>> m_controllers;
};

#endif // CONTROLLERS_CONTROLLERMANAGER_H