QT += core
QT += network
QT -= gui

CONFIG += c++11

TARGET = LinkServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    acceptor.cpp \
    service.cpp \
    idcreator.cpp \
    messagetask.cpp \
    server.cpp

HEADERS += \
    acceptor.h \
    service.h \
    idcreator.h \
    messagetask.h \
    server.h
