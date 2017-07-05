#-------------------------------------------------
#
# Project created by QtCreator 2017-07-01T21:25:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UserInterface
TEMPLATE = app


SOURCES += main.cpp\
        chessboard.cpp \
    Bishop.cpp \
    Cannon.cpp \
    ChessController.cpp \
    Chessman.cpp \
    King.cpp \
    Knight.cpp \
    Mandarin.cpp \
    Pawn.cpp \
    Rook.cpp

HEADERS  += chessboard.h \
    AllChess.h \
    Bishop.h \
    Cannon.h \
    ChessController.h \
    Chessman.h \
    King.h \
    Knight.h \
    Mandarin.h \
    Pawn.h \
    Rook.h

FORMS    += chessboard.ui

RESOURCES += \
    chessboard_and_chessman.qrc

DISTFILES += \
    Images/BishopB.GIF \
    Images/BishopsB.GIF \
    Images/Cannon.GIF \
    Images/CannonR.GIF \
    Images/CannonR2.GIF \
    Images/Cannons.GIF \
    Images/King.GIF \
    Images/KingR.GIF \
    Images/KingRS.GIF \
    Images/Kings.GIF \
    Images/Knight.GIF \
    Images/KnightR.GIF \
    Images/KnightRS.GIF \
    Images/Knights.GIF \
    Images/Mandarin.GIF \
    Images/MandarinR.GIF \
    Images/MandarinRS.GIF \
    Images/Mandarins.GIF \
    Images/OOS.GIF \
    Images/pawn.GIF \
    Images/PawnR.GIF \
    Images/PawnRS.GIF \
    Images/pawns.GIF \
    Images/RB.GIF \
    Images/RBS.GIF \
    Images/Rook.GIF \
    Images/RookR.GIF \
    Images/RookRS.GIF \
    Images/rooks.GIF
