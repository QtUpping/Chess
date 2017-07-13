#include "mytcpsocket.h"
//#include <QTcpSocket>

myTcpSocket::myTcpSocket(qintptr socketDescriptor, QObject *parent)
    :QTcpSocket(parent), socketID(socketDescriptor)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(noArgTrans()));
}

//µÃµ½socketDescriptor
//void myTcpSocket::noArgTrans()
//{
//    emit sendDescriptor(socketID);
//}

void myTcpSocket::noArgTrans()
{
    emit sendDescriptor(socketID);
}

//void myTcpSocket::sendDescriptor(qintptr Descriptor){}
