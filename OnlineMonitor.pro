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
    mybutton.cpp \
    registerw.cpp \
    json.c \
    mainwidget.cpp \
    about.cpp \
    errorlabel.cpp

HEADERS  += control.h \
    login.h \
    mybutton.h \
    SqlConn.h \
    registerw.h \
    json.h \
    mainwidget.h \
    about.h \
    errorlabel.h

FORMS    += control.ui \
    login.ui \
    registerw.ui \
    mainwidget.ui \
    about.ui

RESOURCES += \
    resources.qrc
