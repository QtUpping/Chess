#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <qdebug.h>


class Account
{
public:
    Account();
    void addAccount(QSqlQuery* query, QString account, QString password);
    bool searchAccount(QString account, char* info, QString* qsMes);
    void changeData(QString outcome);
};

#endif // ACCOUNT_H
