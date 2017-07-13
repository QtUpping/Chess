#include "logindlg.h"
#include "ui_logindlg.h"
#include"QMessageBox"
#include<QWidget>
#include<QPainter>
logindlg::logindlg(Client* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindlg)
{

    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
    status=-1;
    connect(this, SIGNAL(sendMes(QString,QString)), this, SLOT(sendMesSlot(QString,QString)));
    this->client = client;
}

logindlg::~logindlg()
{
    delete ui;
}


void logindlg::on_Login_button_clicked()
{
    QString account = ui->usrLineEdit->text();
    QString password = ui->pwdLineEdit->text();
    emit sendMes(account, password);
}

void logindlg::sendMesSlot(QString account, QString password)
{
    QString str = "account";
    str+=account;
    str+=",";
    str+=password;
    client->sendMesg(str);
    this->close();
}

void logindlg::on_Cancle_button_clicked()
{
    this->close();
    qApp->quit();
}

void logindlg::on_pushButton_clicked()
{

}
