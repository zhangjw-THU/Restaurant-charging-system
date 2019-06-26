#include "manager.h"
#include "ui_manager.h"
#include"login.h"
#include<QString>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QtSql>
#include <QtGui>
manager::manager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager)
{
    ui->setupUi(this);

    //显示厨师
    modelo =new QSqlTableModel(this);
    modelo->setTable("manageo");
    modelo->select();
    ui->tableView->setModel(modelo);

    //显示服务员
    modelt =new QSqlTableModel(this);
    modelt->setTable("managet");
    modelt->select();
    ui->tableView_2->setModel(modelt);
}

manager::~manager()
{
    modelt->setTable("managet");
    modelt->select();
    delete ui;
}
//显示服务员菜单
void manager::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    modelt->setTable("managet");
    modelt->select();
    QSqlQuery query;
    query.exec(QString("select * from managet"));

}
//显示厨师菜单
void manager::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    modelo->setTable("manageo");
    modelo->select();
    QSqlQuery query;
    query.exec(QString("select * from manageo"));

}
//退出
void manager::on_pushButton_3_clicked()
{
    QMessageBox::information(this,"Thank you","退出成功！");
    this->close();
    login * l=new login;
    l->show();
}
