#include "account.h"

Account::Account()
{
    QSqlDatabase account = QSqlDatabase::addDatabase("QSQLITE");
    account.setDatabaseName("/Users/wangwei/MyFile/Learning/Computer/Software/QT/Learn1/serverWithArray/serverWithArray/Account.db");
    if(!account.open())
    {
        qDebug()<<"mmp";
    }
    QSqlQuery query;
    query.exec("create table users(id varchar(20) primary key,"
                "password varchar(20), win int, lose int)");
}

void Account::addAccount(QSqlQuery* query, QString account, QString password)
{
    QString command = "insert into users values('";
    command += account;
    command += "','";
    command += password;
    command += "',0,0)";
    (*query).exec(command);
}

bool Account::searchAccount(QString account, char* info, QString* qsMes)
{
    QString qsl;
    QString dou = ",";
    QString accountNumber, password;
    int pos = 0;
    pos = account.indexOf(dou);
    accountNumber = account.left(pos);
    password = account.mid(pos+1);
//    QByteArray qba = account.toLatin1();
    QByteArray qAccount = accountNumber.toLatin1();
    strcpy(info, qAccount.data());
    qsl = "select * from users where id = '" + accountNumber + "'";
    QSqlQuery query(qsl);
    if(!query.next())
    {
        strcat(info, ",0,0");
        QString qMes = QString(QLatin1String(info));
        (*qsMes) = qMes;
        addAccount(&query, accountNumber, password);
        return true;
    }
    else
    {        
        bool whether =  password == query.value(1).toString();
        if(whether)
        {
            int win =  query.value(2).toInt();
            int lose = query.value(3).toInt();
            QString sWin, sLose;
            sWin = QString::number(win, 10);
            sLose = QString::number(lose, 10);
            QByteArray bWin, bLose;
            bWin = sWin.toLatin1();
            bLose = sLose.toLatin1();
            strcat(info, ",");
            strcat(info, bWin.data());
            strcat(info, ",");
            strcat(info, bLose.data());
            QString qMes = QString(QLatin1String(info));
            (*qsMes) = qMes;
        }
        return whether;
    }
}

void Account::changeData(QString outcome)
{
    int pos = outcome.indexOf(",");
    QString account = outcome.left(pos);
    QString qOutcome = outcome.mid(pos+1);
    QString command = "select * from users where id = '" + account + "'";
    QSqlQuery query(command);
    query.next();
    if(!qOutcome.toInt())
    {
        int lose = query.value(3).toInt();
        lose += 1;
        QString command = QString("update users set lose = %1 where id = '%2'").arg(lose).arg(account);
        query.exec(command);
    }
    else
    {
        int win = query.value(2).toInt();
        win += 1;
        QString command = QString("update users set win = %1 where id = '%2'").arg(win).arg(account);
        query.exec(command);
    }
}
