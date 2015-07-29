#-------------------------------------------------
#
# Project created by QtCreator 2015-07-17T14:56:10
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Localize-barcode
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    barcode_locator.cpp

LIBS += `pkg-config opencv --libs`

HEADERS += \
    barcode_locator.h
