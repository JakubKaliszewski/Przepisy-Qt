#-------------------------------------------------
#
# Project created by QtCreator 2017-05-01T14:17:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Przepisy
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    dodajprzepis.cpp \
    nowyskladnik.cpp \
    wybierzskladniki.cpp \
    klasy.cpp

HEADERS  += mainwindow.h \
    initdb.h \
    dodajprzepis.h \
    nowyskladnik.h \
    wybierzskladniki.h \
    klasy.h

FORMS    += mainwindow.ui \
    dodajprzepis.ui \
    nowyskladnik.ui \
    wybierzskladniki.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
