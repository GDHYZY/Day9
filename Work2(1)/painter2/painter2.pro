#-------------------------------------------------
#
# Project created by QtCreator 2014-07-22T12:35:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = painter2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    newdialog.cpp \
    painter.cpp \
    test.cpp

HEADERS  += mainwindow.h \
    newdialog.h \
    painter.h \
    test.h

FORMS    += mainwindow.ui

RESOURCES += \
    image.qrc
