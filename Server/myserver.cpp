#include "myserver.h"

myserver::myserver(QObject *parent):QTcpServer(parent){}

void myserver::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"New connection!!";
    qDebug()<<socketDescriptor;
    tcpSocket = new myTcpSocket(socketDescriptor, this);
    tcpSocket->setSocketDescriptor(socketDescriptor);
    socketList.push_back(tcpSocket);
    listOfDescriptor.push_back(socketDescriptor);
    connect(tcpSocket, SIGNAL(sendDescriptor(qintptr)), this, SLOT(readMessage(qintptr)));
//    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(noArgTransport()));
//    connect(this, SIGNAL(emitDescriptor(qint16)), this, SLOT(readMessage(qint16)));
//    emit QTcpServer::newConnection();
}

void myserver::startServer()
{
    int port = 1234;
    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << port << "...";
    }
}

void myserver::readMessage(qintptr socketDescriptor1)
{
    std::list<qint16>::iterator forDes = listOfDescriptor.begin();
    std::list<myTcpSocket*>::iterator forSocArg = socketList.begin();
    std::list<myTcpSocket*>::iterator forSocOth = socketList.begin();
    int j = 0, k = 0, tmp = 0;
    while(forDes != listOfDescriptor.end())
    {
        if(socketDescriptor1 == *forDes)
            break;
        forDes++;
        j++;
    }
    k = j%2==0?j+1:j-1;
    while(tmp != j)
    {
        forSocArg++;
        tmp++;
    }
    tmp = 0;
    while(tmp != k)
    {
        forSocOth++;
        tmp++;
    }
    qDebug()<<k;
    QByteArray qba = (*forSocArg)->readAll();
    qDebug()<<qba;
    (*forSocOth)->write(qba);
    qDebug("send successfully");
}

