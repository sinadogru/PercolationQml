#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QQuickWindow>
#include <QTextStream>

#include "percolation.h"
#include "percolationmanager.h"
#include "registerpercolation.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("Percolation"));
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;

    QCommandLineOption interactiveOption{QStringList{} << "i" << "interactive", "start in interactive mode"};
    parser.addOption(interactiveOption);

    parser.process(app);

    QQmlApplicationEngine engine;
    registerPercolation(&engine);

    PercolationManager manager;

    if (parser.isSet(interactiveOption))
    {
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    }
    else
    {
        manager.activate();
        QTextStream in{stdin};
        auto gridSize = in.readLine();

        manager.setGridSize(gridSize.toInt());

        auto line = QString{};
        while (in.readLineInto(&line))
        {
            QTextStream linein{&line};
            auto x = QString{};
            auto y = QString{};
            linein >> x >> y;
            manager.addOpening(y.toInt(), x.toInt());
        }

        engine.load(QUrl(QStringLiteral("qrc:/blank.qml")));

//        auto rootList = engine.rootObjects();
//        if (!rootList.isEmpty())
//        {
//            if (auto window = qobject_cast<QQuickWindow*>(rootList[0]))
//            {
//                if (auto perc = window->contentItem()->findChild<Percolation*>("perc"))
//                {
//                    qDebug("var");
//                }
//            }
//        }
    }

    return app.exec();
}

