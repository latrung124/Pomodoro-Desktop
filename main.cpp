#include <QGuiApplication>
#include "Controller/SystemController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    SystemController systemController;
    QObject::connect(&systemController, &SystemController::quit, &app, &QGuiApplication::quit);

    systemController.start();

    return app.exec();
}
