#-------------------------------------------------
#
# Project created by QtCreator 2014-07-24T21:34:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = gORL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    processing.cpp \
    result.cpp \
    graph.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    processing.h \
    result.h \
    graph.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    processing.ui \
    result.ui \
    graph.ui

OTHER_FILES += \
    orl.rc \
    cooltext1661496491.png \
    favicon.ico

RESOURCES += \
    Logo.qrc

CONFIG += static

RC_FILE = orl.rc
