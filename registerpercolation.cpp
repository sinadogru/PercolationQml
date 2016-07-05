#include <QQmlEngine>
#include "registerpercolation.h"
#include "percolation.h"
#include "percolationmodel.h"
#include "randomgridgenerator.h"

void registerPercolation(QQmlEngine *engine)
{
    const char * uri = "CSD.Percolation"; // @uri QtQmlTricks.UiElements
    const int    maj = 1;
    const int    min = 0;

    qmlRegisterType<Percolation>(uri, maj, min, "Percolation");
    qmlRegisterType<PercolationModel>(uri, maj, min, "PercolationModel");
    qmlRegisterType<RandomGridGenerator>(uri, maj, min, "RandomGridGenerator");

    if (engine != Q_NULLPTR)
        engine->addImportPath("qrc:///");
    else
        qWarning () << "You didn't pass a QML engine to the register function,"
                    << "some features (mostly plain QML components, and icon theme provider) won't work !";
}
