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
    //�˵������Ĳ˵�
    cmodel= new QSqlTableModel(this);
    cmodel->setTable("cmenu");
    cmodel->select();
    cmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //���ñ༭��

    ui->tableView->setModel(cmodel);
}

chef::~chef()
{
    delete ui;
}
//ˢ�£�Ȼ����ʾ�˵�
void chef::on_pushButton_3_clicked()
{
    cmodel=new QSqlTableModel(this);
    cmodel->setTable("cmenu");
    cmodel->select();
    cmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //���ñ༭��

    ui->tableView->setModel(cmodel);

}
//��ʼ����
void chef::on_pushButton_clicked()
{
    int i=ui->spinBox->value();
    QSqlQuery query;
    query.exec(QString("select * from cmenu where cid='%1'").arg(i));
    query.next();
    query.exec(QString("update cmenu set cstate = '��ʼ����'where cid=('%1')").arg(i));
    //ͬʱ���²˵�
    cmodel=new QSqlTableModel(this);
    cmodel->setTable("cmenu");
    cmodel->select();
    cmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //���ñ༭��

    ui->tableView->setModel(cmodel);
}
//�������
void chef::on_pushButton_2_clicked()
{
    int i=ui->spinBox->value();
    QSqlQuery query;
    query.exec(QString("select * from cmenu where cid='%1'").arg(i));
    query.next();
    query.exec(QString("update cmenu set cstate = '���'where cid=('%1')").arg(i));
    //ͬʱ���²˵�
    cmodel=new QSqlTableModel(this);
    cmodel->setTable("cmenu");
    cmodel->select();
    cmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //���ñ༭��
    ui->tableView->setModel(cmodel);
}
//�˳�
void chef::on_pushButton_4_clicked()
{
    QMessageBox::information(this,"Thank you","�˳��ɹ���");
    this->close();
    login *l=new login;
    l->show();
}
