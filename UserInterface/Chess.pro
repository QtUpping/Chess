#-------------------------------------------------
#
# Project created by QtCreator 2017-07-05T16:23:02
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
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
    Bishop.cpp \
    Cannon.cpp \
    chessboard.cpp \
    ChessController.cpp \
    Chessman.cpp \
    King.cpp \
    Knight.cpp \
    main.cpp \
    Mandarin.cpp \
    Pawn.cpp \
    Rook.cpp \
    client.cpp \
    mytcpsocket.cpp

HEADERS += \
    AllChess.h \
    Bishop.h \
    Cannon.h \
    chessboard.h \
    ChessController.h \
    Chessman.h \
    King.h \
    Knight.h \
    Mandarin.h \
    Pawn.h \
    Rook.h \
    client.h \
    mytcpsocket.h

SUBDIRS += \
    Chess.pro

RESOURCES += \
    chessboard_and_chessman.qrc \
    chessboard.qrc \
    chessicon.qrc \
    chessmanicon.qrc

FORMS += \
    chessboard.ui

DISTFILES +=
