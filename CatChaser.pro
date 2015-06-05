#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T19:57:58
# Name: Annie (Yi-An) Lu
# UID: 604018381
# CatChaser Game
# Date: 4/24/2015
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CatChaser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboard.cpp \
    instruction.cpp

HEADERS  += mainwindow.h \
    gameboard.h \
    instruction.h

FORMS    += mainwindow.ui \
    gameboard.ui \
    instruction.ui

RESOURCES += \
    images.qrc
