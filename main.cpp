#include <QGuiApplication>
#include "Core/Manager/ControllerManager.h"
#include "Controller/SystemController.h"
#include "Controller/ServiceController.h"
#include "Utils/CloudUtility/AuthenticationType.h"

static void registerTypes()
{
    qRegisterMetaType<AuthenticationType>("AuthenticationType");
    qmlRegisterUncreatableType<AuthenticationTypeClass>(
        "App.Enums",                          // QML namespace
        1, 0,                                 // Major and minor versions
        "AuthenticationType",                 // Enum group name in QML
        "Cannot create AuthenticationType in QML. Access enums only.");
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Q_INIT_RESOURCE(ThemeResources);
    registerTypes();

    ControllerManager::instance().addController<SystemController>();
    ControllerManager::instance().addController<ServiceController>();

    auto systemController = ControllerManager::instance().getController<SystemController>();
    QObject::connect(systemController.get(), &SystemController::quit, &app, &QGuiApplication::quit);
    systemController->start();

    auto serviceController = ControllerManager::instance().getController<ServiceController>();
    serviceController->start();

    return app.exec();
}
