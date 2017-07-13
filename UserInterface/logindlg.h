#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include<QtGui>
#include<QFrame>
#include "client.h"

namespace Ui {
class logindlg;
}

class logindlg : public QDialog
{
    Q_OBJECT

public:
    explicit logindlg(Client* client, QWidget *parent = 0);
    ~logindlg();
    int status;
private slots:
    void on_Login_button_clicked();

    void on_Cancle_button_clicked();

    void on_pushButton_clicked();

    void sendMesSlot(QString account, QString password);

signals:
    void sendMes(QString account, QString password);
private:
    Ui::logindlg *ui;
    Client* client;
};

#endif // LOGINDLG_H
