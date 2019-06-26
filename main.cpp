#include <QApplication>
#include "widget.h"
#include"connection.h"
#include<QTextCodec>
#include<QSqlDatabase>
#include<QDebug>
#include"login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    if(!createConnection()) return 0;
    QSqlDatabase db1=QSqlDatabase::database();
    QSqlQuery query(db1);

    qDebug()<<query.exec("select * from mymenu");
     qDebug()<<query.lastError();
     qDebug()<<query.next();
     while(query.next()){
        qDebug()<<query.value(1);
    }

    login *d=new login;
    d->show();  
    return a.exec();
}
