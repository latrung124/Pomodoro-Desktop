#include <QGuiApplication>
#include <QCoreApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "ThemeConfig/ThemeConfig.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);

    // Create an instance of ThemeConfig
    ThemeConfig themeConfig("qrc:/Resources/theme.json");

    // Expose ThemeConfig to QML
    engine.rootContext()->setContextProperty("themeConfig", &themeConfig);

    engine.loadFromModule("LoginScreen", "LoginScreen");

    return app.exec();
}
