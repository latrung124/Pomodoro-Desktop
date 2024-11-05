#include <QGuiApplication>
#include "System/UiSystemController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Q_INIT_RESOURCE(ThemeResources);

    QObject::connect(UiSystemController::instance(), &UiSystemController::quit, &app, &QGuiApplication::quit);

    UiSystemController::instance()->start();

    return app.exec();
}
