#-------------------------------------------------
#
# Project created by QtCreator 2017-12-16T14:51:17
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OnlineMonitor
TEMPLATE = app


SOURCES += main.cpp\
        control.cpp \
    login.cpp \
    mybutton.cpp

HEADERS  += control.h \
    login.h \
    mybutton.h

FORMS    += control.ui \
    login.ui

RESOURCES += \
    resources.qrc
