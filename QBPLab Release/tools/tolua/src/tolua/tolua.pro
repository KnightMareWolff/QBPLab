#-------------------------------------------------
#
# Project created by QtCreator 2013-10-20T20:38:26
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = tolua
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    LibLUA/lapi.c \
    LibLUA/lauxlib.c \
    LibLUA/lbaselib.c \
    LibLUA/lbitlib.c \
    LibLUA/lcode.c \
    LibLUA/lcorolib.c \
    LibLUA/lctype.c \
    LibLUA/ldblib.c \
    LibLUA/ldebug.c \
    LibLUA/ldo.c \
    LibLUA/ldump.c \
    LibLUA/lfunc.c \
    LibLUA/lgc.c \
    LibLUA/linit.c \
    LibLUA/liolib.c \
    LibLUA/llex.c \
    LibLUA/lmathlib.c \
    LibLUA/lmem.c \
    LibLUA/loadlib.c \
    LibLUA/lobject.c \
    LibLUA/lopcodes.c \
    LibLUA/loslib.c \
    LibLUA/lparser.c \
    LibLUA/lstate.c \
    LibLUA/lstring.c \
    LibLUA/lstrlib.c \
    LibLUA/ltable.c \
    LibLUA/ltablib.c \
    LibLUA/ltm.c \
    LibLUA/lundump.c \
    LibLUA/lvm.c \
    LibLUA/lzio.c \
    LibToLUA/tolua_event.c \
    LibToLUA/tolua_is.c \
    LibToLUA/tolua_map.c \
    LibToLUA/tolua_push.c \
    LibToLUA/tolua_to.c \
    toluabind.c \
    tolua.c

HEADERS += \
    LibLUA/lapi.h \
    LibLUA/lauxlib.h \
    LibLUA/lcode.h \
    LibLUA/lctype.h \
    LibLUA/ldebug.h \
    LibLUA/ldo.h \
    LibLUA/lfunc.h \
    LibLUA/lgc.h \
    LibLUA/llex.h \
    LibLUA/llimits.h \
    LibLUA/lmem.h \
    LibLUA/lobject.h \
    LibLUA/lopcodes.h \
    LibLUA/lparser.h \
    LibLUA/lstate.h \
    LibLUA/lstring.h \
    LibLUA/ltable.h \
    LibLUA/ltm.h \
    LibLUA/lua.h \
    LibLUA/lua.hpp \
    LibLUA/luaconf.h \
    LibLUA/lualib.h \
    LibLUA/lundump.h \
    LibLUA/lvm.h \
    LibLUA/lzio.h \
    LibToLUA/tolua.h \
    LibToLUA/tolua_event.h
