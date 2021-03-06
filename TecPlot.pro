#-------------------------------------------------
#
# Project created by QtCreator 2019-03-22T22:10:29
#
#-------------------------------------------------

QT       -= gui

TARGET = TecPlot
TEMPLATE = lib

DEFINES += TECPLOT_LIBRARY QT_USE_QSTRINGBUILDER

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
        src

SOURCES += \
        src/tecplot.cpp \
    src/teczone.cpp \
    src/teczonereader.cpp

HEADERS += \
        src/tecplot.h \
        src/tecplot_global.h \
    src/teczone.h \
    src/teczonereader.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
