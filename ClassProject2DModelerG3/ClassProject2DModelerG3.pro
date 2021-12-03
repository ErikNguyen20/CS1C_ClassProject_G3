#-------------------------------------------------
#
# Project created by QtCreator 2021-11-04T15:51:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClassProject2DModelerG3
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


SOURCES += \
    _circle.cpp \
    _ellipse.cpp \
    _line.cpp \
    _originbasedshape.cpp \
    _polygon.cpp \
    _polyline.cpp \
    _polyshape.cpp \
    _rectangle.cpp \
    _shape.cpp \
    _square.cpp \
    _text.cpp \
    contactus.cpp \
        main.cpp \
        mainwindow.cpp \
    renderarea.cpp \
    loginwindow.cpp \
    testimonials.cpp

HEADERS += \
    _circle.h \
    _ellipse.h \
    _line.h \
    _originbasedshape.h \
    _polygon.h \
    _polyline.h \
    _polyshape.h \
    _rectangle.h \
    _shape.h \
    _square.h \
    _text.h \
    contactus.h \
        mainwindow.h \
    shapemaster.h \
    testimonials.h \
    vector.h \
    renderarea.h \
    loginwindow.h \
    parserexception.h

FORMS += \
    contactus.ui \
        mainwindow.ui \
    loginwindow.ui \
    testimonials.ui

DISTFILES += \
    midnight-oil.jpg \
    testimonials.txt

RESOURCES += \
    resources.qrc
