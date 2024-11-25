#include <QGuiApplication>
#include "Controller/SystemController.h"
#include "Controller/ServiceController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Q_INIT_RESOURCE(ThemeResources);

    SystemController systemController;
    QObject::connect(&systemController, &SystemController::quit, &app, &QGuiApplication::quit);

    systemController.start();
    
    ServiceController serviceController;
    serviceController.start();

    return app.exec();
}
