#include "chef.h"
#include"login.h"
#include "ui_chef.h"
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
chef::chef(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chef)
{
    ui->setupUi(this);
    //菜单传来的菜单
    cmodel= new QSqlTableModel(this);
    cmodel->setTable("cmenu");
    cmodel->select();
    cmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置编辑策

    ui->tableView->setModel(cmodel);
}

chef::~chef()
{
    delete ui;
}
//刷新，然后显示菜单
void chef::on_pushButton_3_clicked()
{
    cmodel=new QSqlTableModel(this);
    cmodel->setTable("cmenu");
    cmodel->select();
    cmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置编辑策

    ui->tableView->setModel(cmodel);

}
//开始做菜
void chef::on_pushButton_clicked()
{
    int i=ui->spinBox->value();
    QSqlQuery query;
    query.exec(QString("select * from cmenu where cid='%1'").arg(i));
    query.next();
    query.exec(QString("update cmenu set cstate = '开始做菜'where cid=('%1')").arg(i));
    //同时更新菜单
    cmodel=new QSqlTableModel(this);
    cmodel->setTable("cmenu");
    cmodel->select();
    cmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置编辑策

    ui->tableView->setModel(cmodel);
}
//完成做菜
void chef::on_pushButton_2_clicked()
{
    int i=ui->spinBox->value();
    QSqlQuery query;
    query.exec(QString("select * from cmenu where cid='%1'").arg(i));
    query.next();
    query.exec(QString("update cmenu set cstate = '完成'where cid=('%1')").arg(i));
    //同时更新菜单
    cmodel=new QSqlTableModel(this);
    cmodel->setTable("cmenu");
    cmodel->select();
    cmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置编辑策
    ui->tableView->setModel(cmodel);
}
//退出
void chef::on_pushButton_4_clicked()
{
    QMessageBox::information(this,"Thank you","退出成功！");
    this->close();
    login *l=new login;
    l->show();
}
