#-------------------------------------------------
#
# Project created by QtCreator 2015-03-17T21:09:22
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tanks

CONFIG += C++11

TEMPLATE = app


SOURCES += main.cpp\
        tanksgui.cpp \
    general_types.cpp \
    logic/logic.cpp

HEADERS  += tanksgui.h \
    graph/interface.h \
    gui/interface.h \
    logic/interface.h \
    map/interface.h \
    player/interface.h \
    general_types.h \
    interface.h

FORMS    += tanksgui.ui
