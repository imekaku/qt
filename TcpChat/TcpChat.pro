#-------------------------------------------------
#
# Project created by QtCreator 2015-09-24T09:22:37
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpChat
TEMPLATE = app


SOURCES += main.cpp\
        tcpchatwidget.cpp

HEADERS  += tcpchatwidget.h

FORMS    += tcpchatwidget.ui
