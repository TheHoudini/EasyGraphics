#-------------------------------------------------
#
# Project created by QtCreator 2015-08-28T09:25:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyGraphic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    modelmanager.cpp \
    painters/imagedatapainter.cpp \
    tgaimage.cpp

HEADERS  += mainwindow.h \
    modelmanager.h \
    painters/imagedatapainter.h \
    tgaimage.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

DISTFILES +=
