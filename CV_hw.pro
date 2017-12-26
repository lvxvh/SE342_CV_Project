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
    iconhelper.cpp \
    hsldialog.cpp \
    qhsl.cpp \
    mslider.cpp \
    historydialog.cpp \
    binarydialog.cpp \
    scaledialog.cpp \
    rotatedialog.cpp \
    aopdialog.cpp \
    mylabel.cpp \
    cropdialog.cpp \
    contrastlinerdialog.cpp \
    contrastcruvedialog.cpp \
    histogramdialog.cpp \
    filterdialog.cpp \
    parameterdialog.cpp \
    bmbasicdialog.cpp \
    dtdialog.cpp \
    skeletondialog.cpp

HEADERS  += mainwindow.h \
    imageholder.h \
    iconhelper.h \
    hsldialog.h \
    qhsl.h \
    mslider.h \
    historydialog.h \
    binarydialog.h \
    scaledialog.h \
    rotatedialog.h \
    aopdialog.h \
    croprect.h \
    mylabel.h \
    cropdialog.h \
    contrastlinerdialog.h \
    contrastcruvedialog.h \
    histogramdialog.h \
    filterdialog.h \
    parameterdialog.h \
    bmbasicdialog.h \
    dtdialog.h \
    skeletondialog.h

FORMS    += mainwindow.ui \
    hsldialog.ui \
    historydialog.ui \
    binarydialog.ui \
    scaledialog.ui \
    rotatedialog.ui \
    aopdialog.ui \
    cropdialog.ui \
    photoshotdialog.ui \
    contrastlinerdialog.ui \
    contrastcruvedialog.ui \
    histogramdialog.ui \
    filterdialog.ui \
    parameterdialog.ui \
    bmbasicdialog.ui \
    dtdialog.ui \
    skeletondialog.ui

RESOURCES += \
    style.qrc \
    image.qrc
