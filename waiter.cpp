#include "waiter.h"
#include "ui_waiter.h"
#include"login.h"
#include"charge.h"
#include"chargew.h"
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
waiter::waiter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waiter)
{
    //��ʾ�ѵ�˵�
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("ydcaidan");
    model->select();
    //���ñ༭����
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_2->setModel(model);
    //��ʾ���˽���
    amodel=new QSqlTableModel(this);
    amodel->setTable("cmenu");
    amodel->select();
    amodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(amodel);
    //��ʾ�˿���Ϣ
    bmodel=new QSqlTableModel(this);

    bmodel->setTable("ginfo");
    bmodel->select();
    bmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_3->setModel(bmodel);
    QSqlQuery query;
    query.exec(QString("select * from ydcaidan"));
    double sum=0;
    while(query.next())
    {
        sum+=query.value(2).toDouble()*query.value(3).toDouble();
        qDebug()<<sum;
    }
    ui->lineEdit->setText(QString::number(sum));

}

waiter::~waiter()
{
    delete ui;
}
//�ѵ�˵����б�
void waiter::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    model = new QSqlTableModel(this);
    model->setTable("ydcaidan");
    model->select();
    //���ñ༭����
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_2->setModel(model);

}


//��ʾ���˽���

void waiter::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    model = new QSqlTableModel(this);
    model->setTable("cmenu");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
}
//ˢ��
void waiter::on_pushButton_3_clicked()
{
    model = new QSqlTableModel(this);
    model->setTable("ydcaidan");
    model->select();
    //���ñ༭����
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_2->setModel(model);
    //��ʾ���˽���
    amodel=new QSqlTableModel(this);
    amodel->setTable("cmenu");
    amodel->select();
    amodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(amodel);
    //��ʾ�˿���Ϣ
    bmodel=new QSqlTableModel(this);

    bmodel->setTable("ginfo");
    bmodel->select();
    bmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_3->setModel(bmodel);
}
//������Ϣ
void waiter::on_pushButton_4_clicked()
{
    QSqlQuery query;
    query.exec(QString("delete from ginfo"));
}
//�˳�
void waiter::on_pushButton_5_clicked()
{
    QMessageBox::information(this,"Thank you","�˳��ɹ���");
    this->close();
    login * l=new login;
    l->show();
}
//����
void waiter::on_pushButton_6_clicked()
{
    double a,b,c;
    a=ui->lineEdit->text().toDouble();
    b=ui->lineEdit_2->text().toDouble();
    c=b-a;
    ui->lineEdit_3->setText(QString::number(c));
}
//֧����֧��
void waiter::on_pushButton_7_clicked()
{
    charge *c=new charge;
    c->show();
}
//΢��֧��
void waiter::on_pushButton_8_clicked()
{
    chargew *w=new chargew;
    w->show();
}
