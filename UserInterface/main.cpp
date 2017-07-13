#include "chessboard.h"
#include <QApplication>
#include "client.h"
#include "logindlg.h"
#include <ChessController.h>
class ChessController;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client;
    ChessBoard w(&client);
    w.setGeometry(350,50,1200,960);
    w.setMaximumSize(1200,960);
    w.setMinimumSize(1200, 960);
    w.setWindowOpacity(0.9);
    w.show();
    return a.exec();
}


