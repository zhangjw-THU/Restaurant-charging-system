#-------------------------------------------------
#
# Project created by QtCreator 2017-09-11T18:26:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = restaurant
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    guest.cpp \
    login.cpp \
    chef.cpp \
    waiter.cpp \
    manager.cpp \
    charge.cpp \
    chargew.cpp

HEADERS  += widget.h \
    connection.h \
    guest.h \
    login.h \
    chef.h \
    waiter.h \
    manager.h \
    charge.h \
    chargew.h

FORMS    += widget.ui \
    guest.ui \
    login.ui \
    chef.ui \
    waiter.ui \
    manager.ui \
    charge.ui \
    chargew.ui

QT += sql

RESOURCES += \
    image.qrc

