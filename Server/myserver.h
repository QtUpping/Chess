#ifndef MYSERVER_H
#define MYSERVER_H
#include "mytcpsocket.h"
#include <QtNetwork>
#include <stdlib.h>
#include <list>
using namespace  std;

class myserver : public QTcpServer
{
    Q_OBJECT

public:
    explicit myserver(QObject *parent = 0);
    void startServer();

private:
    myTcpSocket* tcpSocket;
    QTcpServer* tcpServer;
    std::list<myTcpSocket*> socketList;
    std::list<qint16>listOfDescriptor;
    int numOfConnection;

protected:
    void incomingConnection(qintptr socketDescriptor);

private slots:
    void readMessage(qintptr);
};

#endif // MYSERVER_H
