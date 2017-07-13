#ifndef CLIENT_H
#define CLIENT_H
#include <QtNetwork>
//#include "mytcpsocket.h"


class Client : public QObject
{
    Q_OBJECT
public:
    Client();

private:
    void connectServer();
    QTcpSocket* tcpSocket;

signals:
    void sendPoint(QString chessPoint);

private slots:
    void readMesg();

public slots:
    void sendMesg(QString desPoint);
};

#endif // CLIENT_H
