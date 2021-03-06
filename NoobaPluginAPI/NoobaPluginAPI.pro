#-------------------------------------------------
#
# Project created by QtCreator 2013-04-01T12:18:25
#
#-------------------------------------------------

QT       += core gui

TEMPLATE = lib
CONFIG += staticlib

#win32:TEMPLATE = vclib

CONFIG(debug, debug|release):    message(API Debug build!)
CONFIG(release, debug|release):    message(API Release build!)

CONFIG(release, debug|release): TARGET = NoobaPluginAPI
CONFIG(debug, debug|release): TARGET = NoobaPluginAPId

CONFIG(debug, debug|release):DESTDIR = $$PWD/../../NoobaVSS_build/NoobaPluginAPI/Debug/
CONFIG(release, debug|release):DESTDIR = $$PWD/../../NoobaVSS_build/NoobaPluginAPI/Release/

DEFINES += NOOBAPLUGINAPI_LIBRARY

SOURCES += \
    noobapluginbase.cpp \
    noobapluginbaseprivate.cpp \
    noobapluginapi.cpp \
    procparams.cpp \
    pluginpassdata.cpp \
    plugininfo.cpp

HEADERS += noobapluginapi.h\
        NoobaPluginAPI_global.h \
    noobapluginbase.h \
    noobapluginbaseprivate.h \
    nooba.h \
    procparams.h \
    pluginpassdata.h \
    plugininfo.h
