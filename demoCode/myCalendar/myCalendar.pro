#-------------------------------------------------
#
# Project created by QtCreator 2016-08-01T10:24:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myCalendar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    draglabel.cpp \
    heheda.cpp \
    dndlistwidget.cpp \
    colorlisteditor.cpp

HEADERS  += mainwindow.h \
    draglabel.h \
    heheda.h \
    dndlistwidget.h \
    colorlisteditor.h

FORMS    += mainwindow.ui

TRANSLATIONS += cn.ts
