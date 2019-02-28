#-------------------------------------------------
#
# Project created by QtCreator 2019-01-27T10:12:24
#
#-------------------------------------------------

QT  += core gui
#QT  += core   gui   multimediamulti   mediawidgets

QT  += multimedia
QT  +=  multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CONNECT_FOUR_GMAE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

 DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG +=   c++11

SOURCES += \
        main.cpp \
    error.cpp \
    test.cpp \
    easy.cpp \
    normal.cpp \
    image.cpp \
    beginpage.cpp \
    mainwindow.cpp \
    connect.cpp \
    hard.cpp \
    over.cpp \
    resultpage.cpp \
    pushobject.cpp

HEADERS += \
    error.h \
    test.h \
    easy.h \
    normal.h \
    image.h \
    beginpage.h \
    mainwindow.h \
    connect.h \
    hard.h \
    over.h \
    resultpage.h \
    pushobject.h


FORMS += \
        mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
