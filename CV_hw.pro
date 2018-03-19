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


SOURCES += sources/main.cpp\
        sources/mainwindow.cpp \
    sources/imageholder.cpp \
    sources/utils/iconhelper.cpp \
    sources/dialogs/hsldialog.cpp \
    sources/utils/qhsl.cpp \
    sources/utils/mslider.cpp \
    sources/dialogs/historydialog.cpp \
    sources/dialogs/binarydialog.cpp \
    sources/dialogs/scaledialog.cpp \
    sources/dialogs/rotatedialog.cpp \
    sources/dialogs/aopdialog.cpp \
    sources/utils/mylabel.cpp \
    sources/dialogs/cropdialog.cpp \
    sources/dialogs/contrastlinerdialog.cpp \
    sources/dialogs/contrastcruvedialog.cpp \
    sources/dialogs/histogramdialog.cpp \
    sources/dialogs/filterdialog.cpp \
    sources/dialogs/parameterdialog.cpp \
    sources/dialogs/bmbasicdialog.cpp \
    sources/dialogs/dtdialog.cpp \
    sources/dialogs/skeletondialog.cpp \
    sources/dialogs/watersheddialog.cpp

HEADERS  += headers/mainwindow.h \
    headers/imageholder.h \
    headers/iconhelper.h \
    headers/hsldialog.h \
    headers/qhsl.h \
    headers/mslider.h \
    headers/historydialog.h \
    headers/binarydialog.h \
    headers/scaledialog.h \
    headers/rotatedialog.h \
    headers/aopdialog.h \
    headers/croprect.h \
    headers/mylabel.h \
    headers/cropdialog.h \
    headers/contrastlinerdialog.h \
    headers/contrastcruvedialog.h \
    headers/histogramdialog.h \
    headers/filterdialog.h \
    headers/parameterdialog.h \
    headers/bmbasicdialog.h \
    headers/dtdialog.h \
    headers/skeletondialog.h \
    headers/watersheddialog.h

FORMS    += forms/mainwindow.ui \
    forms/hsldialog.ui \
    forms/historydialog.ui \
    forms/binarydialog.ui \
    forms/scaledialog.ui \
    forms/rotatedialog.ui \
    forms/aopdialog.ui \
    forms/cropdialog.ui \
    forms/photoshotdialog.ui \
    forms/contrastlinerdialog.ui \
    forms/contrastcruvedialog.ui \
    forms/histogramdialog.ui \
    forms/filterdialog.ui \
    forms/parameterdialog.ui \
    forms/bmbasicdialog.ui \
    forms/dtdialog.ui \
    forms/skeletondialog.ui \
    forms/watersheddialog.ui

RESOURCES += \
    style.qrc \
    image.qrc
