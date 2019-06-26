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

    //��ʾ��ʦ
    modelo =new QSqlTableModel(this);
    modelo->setTable("manageo");
    modelo->select();
    ui->tableView->setModel(modelo);

    //��ʾ����Ա
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
//��ʾ����Ա�˵�
void manager::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    modelt->setTable("managet");
    modelt->select();
    QSqlQuery query;
    query.exec(QString("select * from managet"));

}
//��ʾ��ʦ�˵�
void manager::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    modelo->setTable("manageo");
    modelo->select();
    QSqlQuery query;
    query.exec(QString("select * from manageo"));

}
//�˳�
void manager::on_pushButton_3_clicked()
{
    QMessageBox::information(this,"Thank you","�˳��ɹ���");
    this->close();
    login * l=new login;
    l->show();
}
