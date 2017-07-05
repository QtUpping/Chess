#include "chessboard.h"
#include <QApplication>

#include <ChessController.h>
class ChessController;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChessBoard w;
    w.setGeometry(350,50,1200,960);
    w.setMaximumSize(1200,960);
    w.show();
    ChessController tmp;
    return a.exec();
}


