#include <QGuiApplication>
#include "Core/Manager/ControllerManager.h"
#include "Controller/SystemController.h"
#include "Controller/ServiceController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Q_INIT_RESOURCE(ThemeResources);

    ControllerManager::instance().addController<SystemController>();
    ControllerManager::instance().addController<ServiceController>();

    auto systemController = ControllerManager::instance().getController<SystemController>();
    QObject::connect(systemController.get(), &SystemController::quit, &app, &QGuiApplication::quit);
    systemController->start();

    auto serviceController = ControllerManager::instance().getController<ServiceController>();
    serviceController->start();

    return app.exec();
}
