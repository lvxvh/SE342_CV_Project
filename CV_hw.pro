#-------------------------------------------------
#
# Project created by QtCreator 2017-12-05T21:07:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CV_hw
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
    imageholder.cpp \
    detailwindow.cpp \
    iconhelper.cpp \
    hsldialog.cpp \
    qhsl.cpp \
    mslider.cpp \
    historydialog.cpp

HEADERS  += mainwindow.h \
    imageholder.h \
    detailwindow.h \
    iconhelper.h \
    hsldialog.h \
    qhsl.h \
    mslider.h \
    historydialog.h

FORMS    += mainwindow.ui \
    hsldialog.ui \
    historydialog.ui

RESOURCES += \
    style.qrc
