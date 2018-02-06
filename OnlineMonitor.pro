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
    errorlabel.cpp \
    SqlConn.cpp \
    mymessagebox.cpp \
    maincontrol.cpp \
    chgpsd.cpp \
    peoplemgr.cpp \
    citymgr.cpp \
    chgvalue.cpp \
    addcity.cpp \
    detail.cpp

HEADERS  += control.h \
    login.h \
    mybutton.h \
    SqlConn.h \
    registerw.h \
    json.h \
    mainwidget.h \
    about.h \
    errorlabel.h \
    mymessagebox.h \
    maincontrol.h \
    chgpsd.h \
    peoplemgr.h \
    citymgr.h \
    chgvalue.h \
    addcity.h \
    detail.h

FORMS    += control.ui \
    login.ui \
    registerw.ui \
    mainwidget.ui \
    about.ui \
    mymessagebox.ui \
    maincontrol.ui \
    chgpsd.ui \
    peoplemgr.ui \
    citymgr.ui \
    chgvalue.ui \
    addcity.ui \
    detail.ui

RESOURCES += \
    resources.qrc
