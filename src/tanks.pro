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
    logic/logic.cpp \
    map/map.cpp \
    player/player.cpp \
    player/bullet.cpp \
    graph/graphicmanager.cpp \
    graph/renderGL.cpp \
    graph/sprite.cpp \
    graph/spritemanager.cpp

HEADERS  += tanksgui.h \
    graph/interface.h \
    logic/interface.h \
    map/interface.h \
    player/interface.h \
    general_types.h \
    graph/graphicmanager.h \
    graph/sprite.h \
    graph/spritemanager.h \
    graph/graphinclude.h

INCLUDEPATH += ../libs

FORMS    += tanksgui.ui

DISTFILES += \
    graph/ReadMe.txt \
    ../conf/map.json \
    ../conf/square.tmap
