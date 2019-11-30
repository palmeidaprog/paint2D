#-------------------------------------------------
#
# Project created by QtCreator 2019-08-14T09:21:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = paint2D
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglpanel.cpp \
    paintobject.cpp \
    transformation.cpp \
    objectscontroller.cpp

HEADERS  += mainwindow.h \
    openglpanel.h \
    paintobject.h \
    transformationtype.h \
    transformation.h \
    objectscontroller.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

