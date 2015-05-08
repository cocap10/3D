#-------------------------------------------------
#
# Project created by QtCreator 2013-09-25T09:11:42
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyOpenGL
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    myglwidget.cpp \
    bras.cpp \
    arene.cpp \
    point.cpp \
    loadtgadisplaycdv.cpp

HEADERS  += window.h \
    myglwidget.h \
    bras.h \
    arene.h \
    point.h \
    loadtgadisplaycdv.h

FORMS    += window.ui \
    window.ui

LIBS     += -lGLU
