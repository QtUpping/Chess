#include "client.h"

Client::Client()
{
    connectServer();
}

void Client::connectServer()
{
    tcpSocket = new QTcpSocket(this);
    tcpSocket->abort();
    tcpSocket->connectToHost("192.168.1.101",1234);
    tcpSocket->waitForConnected();
    this->connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMesg()));
}

void Client::readMesg()
{
    QByteArray message = tcpSocket->readAll();
    qDebug()<<message;
    QString newPoint = QVariant(message).toString();
    qDebug("receive successfully0");
    emit sendPoint(newPoint);
    qDebug("receive successfully1");
}

void Client::sendMesg(QString desPoint)
{
    tcpSocket->write(desPoint.toStdString().c_str(),
                     strlen(desPoint.toStdString().c_str()));
    tcpSocket->waitForBytesWritten();
}

//void Client::sendPoint(QString chessPoint){}
