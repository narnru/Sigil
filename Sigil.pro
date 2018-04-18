#-------------------------------------------------
#
# Project created by QtCreator 2018-03-26T08:56:50
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

RC_FILE = Rc.rc

QMAKE_LFLAGS += -static -static-libgcc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sigil
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    processing.cpp

HEADERS  += mainwindow.h \
    processing.h

FORMS    += mainwindow.ui
