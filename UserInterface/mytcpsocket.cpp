#include "mytcpsocket.h"
//#include <QTcpSocket>

myTcpSocket::myTcpSocket(qintptr socketDescriptor, QObject *parent)
    :QTcpSocket(parent), socketID(socketDescriptor)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(noArgTrans()));
}

//寰楀埌socketDescriptor
//void myTcpSocket::noArgTrans()
//{
//    emit sendDescriptor(socketID);
//}

void myTcpSocket::noArgTrans()
{
    emit sendDescriptor(socketID);
}

//void myTcpSocket::sendDescriptor(qintptr Descriptor){}
