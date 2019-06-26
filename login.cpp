#include "login.h"
#include "ui_login.h"
#include"widget.h"
#include"guest.h"
#include"chef.h"
#include"waiter.h"
#include"connection.h"
#include"manager.h"
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
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    model=new QSqlTableModel(this);
    model->setTable("people");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //connect(*g,SIGNAL(g->on_pushButton_12_clicked()),*w,SLOT(w->messagejs()));

}

login::~login()
{

    delete ui;
}
//�ͻ�
void login::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
//������Ա
void login::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
//�˳�
void login::on_pushButton_6_clicked()
{
    this->close();
}
//ע��
void login::on_pushButton_4_clicked()
{
    model->database().transaction();
    QSqlQuery query;
    query.exec(QString("slect* from user"));
    query.next();
    QString s,p;
    p=ui->lineEdit_5->text();
    s=ui->lineEdit->text();
    if(s.length()!=11||p.length()==0)
    {
        QMessageBox::warning(this,tr("��ʾ"),tr("�����ֻ�������"),QMessageBox::Ok);
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
    }
    else{
        query.exec(QString("insert into cguest values('%1','%2')").arg(s).arg(p));
    QMessageBox::warning(this,tr("��ϲ��"),tr("ע��ɹ������¼"),QMessageBox::Ok);
    //ui->lineEdit->clear();
    ui->lineEdit_5->clear();
    }

}

//��˵�¼��ť��¼����
void login::on_pushButton_3_clicked()
{
    QString s;
    s=ui->lineEdit->text();
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("�������ֻ���"),
                                 tr("���������ֻ����ٵ�¼�����û��ע�ᣬ����ע�ᣡ"),QMessageBox::Ok);
        ui->lineEdit->setFocus();
    }
    else{
        if(s.length()!=11){QMessageBox::warning(this,tr("��ʾ"),tr("�������Ѿ�ע����ֻ��ŵ�½��"),QMessageBox::Ok);
            ui->lineEdit->clear();
            ui->lineEdit->setFocus();}
        else{
            QString s,p;
            s=ui->lineEdit->text();
            p=ui->lineEdit_5->text();
            QSqlQuery query;
            query.exec(QString("select * from cguest where gid = ('%1')").arg(s));
            query.next();

            if(query.value(1)==p){
    guest*g=new guest;
    g->show();
  // this->close();
            }
            else{
                QMessageBox::warning(this,tr("��ʾ"),tr("������˺��ش������������롣"),QMessageBox::Ok);
            }
        }

    }
    ui->lineEdit->clear();
    ui->lineEdit_5->clear();

}
//����ϵͳ��¼��ť
void login::on_pushButton_5_clicked()
{
    if(ui->lineEdit_2->text().isEmpty()){
        QMessageBox::information(this,tr("���������� "),
                                 tr("�������������¼"),QMessageBox::Ok);
        ui->lineEdit_2->setFocus();
    }

    else{
       QSqlQuery query;
       query.exec("select pwd from password");
        query.next();
        if(query.value(0).toString() == ui->lineEdit_2->text()){
 //       if(query.value(0).toString() == "abc"){
            ui->lineEdit_2->clear();
         Widget *w=new Widget;
           w->show();

       }
        else {
           QMessageBox::warning(this, tr("�������"), tr("���������������ȷ�������¼��"), QMessageBox::Ok);
               ui->lineEdit_2->clear();
                    ui->lineEdit_2->setFocus();
       }
    }
    //this->close();
}
//��ʦ��¼
void login::on_pushButton_7_clicked()
{
    if(ui->lineEdit_3->text().isEmpty()){
        QMessageBox::information(this,tr("����������"),tr("�������ʦ�����¼"),QMessageBox::Ok);
        ui->lineEdit_3->setFocus();
    }
    else{
        QSqlQuery query;
        query.exec("select cpwd from cpassword");
        query.next();
        if(query.value(0).toString()==ui->lineEdit_3->text()){
            ui->lineEdit_3->clear();
            chef * c=new chef;
            c->show();
            //this->close();
        }else{
            QMessageBox::warning(this,tr("�������"),tr("����������������룡"),QMessageBox::Ok);
            ui->lineEdit_3->clear();
            ui->lineEdit_3->setFocus();
        }
    }
}
//����Ա��¼
void login::on_pushButton_8_clicked()
{
    if(ui->lineEdit_4->text().isEmpty()){
        QMessageBox::information(this,tr("����������"),tr("���������Ա�����¼"),QMessageBox::Ok);
        ui->lineEdit_4->setFocus();
    }
    else{
        QSqlQuery query;
        query.exec("select wpwd from wpassword");
        query.next();
        if(query.value(0).toString()==ui->lineEdit_4->text()){
            ui->lineEdit_4->clear();
            waiter* w=new waiter;

           // s=w;
             w->show();
            //this->close();
        }else{
            QMessageBox::warning(this,tr("�������"),tr("����������������룡"),QMessageBox::Ok);
            ui->lineEdit_4->clear();
            ui->lineEdit_4->setFocus();
        }
    }
}
//�����¼
void login::on_pushButton_9_clicked()
{
    if(ui->lineEdit_6->text().isEmpty()){
        QMessageBox::information(this,tr("����������"),tr("�����뾭�������¼"),QMessageBox::Ok);
        ui->lineEdit_6->setFocus();
    }
    else{
        QSqlQuery query;
        query.exec("select mpwd from mpassword");
        query.next();
        if(query.value(0).toString()==ui->lineEdit_6->text()){
            ui->lineEdit_6->clear();
          manager * m=new manager;
            m->show();
          //  this->close();
        }else{
            QMessageBox::warning(this,tr("�������"),tr("����������������룡"),QMessageBox::Ok);
            ui->lineEdit_6->clear();
            ui->lineEdit_6->setFocus();
        }
    }
}
