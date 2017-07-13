#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>

class myTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit myTcpSocket(qintptr socketDescriptor, QObject *parent = 0);
    QString myAccount;
signals:
    void sendDescriptor(qintptr Descriptor);

private slots:
    void noArgTrans();
private:
    qintptr socketID;
};

#endif // MYTCPSOCKET_H
