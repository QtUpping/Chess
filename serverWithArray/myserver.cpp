#include "myserver.h"

myserver::myserver(QObject *parent):QTcpServer(parent)
{
    for(int i = 0; i < 20; i++)
    {
        campMesg[i] = 0;
    }
    camp = 1;
}

void myserver::incomingConnection(qintptr socketDescriptor)
{
    tcpSocket = new myTcpSocket(socketDescriptor, this);
    tcpSocket->setSocketDescriptor(socketDescriptor);
    socketList.push_back(tcpSocket);
    listOfDescriptor.push_back(socketDescriptor);
    connect(tcpSocket, SIGNAL(sendDescriptor(qintptr)), this, SLOT(readMessage(qintptr)));
}

void myserver::startServer()
{
    int port = 1234;
    this->listen(QHostAddress::Any,port);
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
    QByteArray qba = (*forSocArg)->readAll();
    QString mes = qba;
    if(mes.startsWith("camp"))
    {
        QByteArray zero = "camp0";
        zero += (*forSocOth)->myAccount.toLatin1();
        QByteArray one = "camp1";
        one += (*forSocArg)->myAccount.toLatin1();
        (*forSocArg)->write(zero);
        (*forSocOth)->write(one);
    }
    else if(mes.startsWith("point"))
    {
        (*forSocOth)->write(qba);
    }
    else if(mes.startsWith("account"))
    {
        QString acc = mes.mid(7);
        char infoChar[40] = {0};
        int log = account.searchAccount(acc, infoChar, &((*forSocArg)->myAccount));
        acc = QString::number(log, 10);
        mes = "account" + acc + QLatin1String(infoChar);
        QByteArray accmes = mes.toLatin1();
        (*forSocArg)->write(accmes);
        if(forSocOth != socketList.end())
        {
            QByteArray ok = ",start";
            (*forSocOth)->write(ok);
            (*forSocArg)->write(ok);
        }
    }
    else if(mes.startsWith("conversation"))
    {
        QByteArray conversation = mes.toLatin1();
        (*forSocOth)->write(conversation);
    }
    else if(mes.startsWith("outcome"))
    {
        int pos = (*forSocArg)->myAccount.indexOf(",");
        QString qaccount = (*forSocArg)->myAccount.left(pos);
        QString outcome = mes.mid(7);
        qaccount += ",";
        qaccount += outcome;
        account.changeData(qaccount);
    }
    else if(mes.startsWith("surrender"))
    {
        int pos1 = (*forSocArg)->myAccount.indexOf(",");
        int pos2 = (*forSocOth)->myAccount.indexOf(",");
        QString qaccount1 = (*forSocArg)->myAccount.left(pos1);
        QString qaccount2 = (*forSocOth)->myAccount.left(pos2);
        qaccount1 += ",0";
        qaccount2 += ",1";
        account.changeData(qaccount1);
        account.changeData(qaccount2);
        QByteArray surrender = "surrender";
        (*forSocOth)->write(surrender);
    }
}

