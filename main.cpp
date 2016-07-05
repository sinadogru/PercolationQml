#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "registerpercolation.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    registerPercolation(&engine);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
