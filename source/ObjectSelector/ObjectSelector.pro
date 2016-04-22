#-------------------------------------------------
#
# Project created by QtCreator 2016-04-03T00:47:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ObjectSelector
TEMPLATE = app

CONFIG += c++11
SOURCES += main.cpp\
        mainwindow.cpp \
        body.cpp \
        bodylauncher.cpp \
        mygraphicsview.cpp \
        mygraphicsscene.cpp

HEADERS  += mainwindow.h \
            body.h \
            bodylauncher.h \
            mygraphicsview.h \
            mygraphicsscene.h


FORMS    += mainwindow.ui
