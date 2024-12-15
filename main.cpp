#include <QGuiApplication>
#include "Core/Helper/ControllerHelper.h"
#include "Controller/SystemController.h"
#include "Controller/ServiceController/ServiceController.h"
#include "Utils/CloudUtility/AuthenticationType.h"
#include "GuiApplication.h"

static void registerTypes()
{
    qRegisterMetaType<AuthenticationType>("AuthenticationType");
    qmlRegisterUncreatableType<AuthenticationTypeClass>(
        "App.Enums",                          // QML namespace
        1, 0,                                 // Major and minor versions
        "AuthenticationType",                 // Enum group name in QML
        "Cannot create AuthenticationType in QML. Access enums only.");
}

static QGuiApplication* app = nullptr;

int main(int argc, char *argv[])
{
    app = new QGuiApplication(argc, argv);
    GuiApplication::setInstance(app);

    Q_INIT_RESOURCE(ThemeResources);
    registerTypes();

    QCoreApplication::setApplicationName("Totodoro");
    QCoreApplication::setOrganizationName("Luminary");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    helper::system::addController<SystemController>();
    helper::system::addController<ServiceController>();

    auto systemController = helper::system::getController<SystemController>();
    QObject::connect(systemController.get(), &SystemController::quit, app, &QGuiApplication::quit);
    systemController->start();

    auto serviceController = helper::system::getController<ServiceController>();
    serviceController->start();

    return app->exec();
}
