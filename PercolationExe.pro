TEMPLATE = app

QT += qml quick
CONFIG += c++14

SOURCES += main.cpp \
    percolation.cpp \
    percolationmodel.cpp \
    registerpercolation.cpp \
    weightedquickunionfind.cpp \
    randomgridgenerator.cpp

HEADERS += percolation.h \
    percolationmodel.h \
    registerpercolation.h \
    weightedquickunionfind.h \
    randomgridgenerator.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

