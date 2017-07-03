#include "chessboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChessBoard w;
    w.setGeometry(350,50,1200,960);
//    w.setStatusBar(0);
//    w.setMinimumSize(1200,960);
//    w.setMaximumHeight(960);
    w.show();

    return a.exec();
}


