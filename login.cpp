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
//¿Í»§
void login::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
//·þÎñÈËÔ±
void login::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
//ÍË³ö
void login::on_pushButton_6_clicked()
{
    this->close();
}
//×¢²á
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
        QMessageBox::warning(this,tr("ÌáÊ¾"),tr("ÊäÈëÊÖ»úºÅÓÐÎó"),QMessageBox::Ok);
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
    }
    else{
        query.exec(QString("insert into cguest values('%1','%2')").arg(s).arg(p));
    QMessageBox::warning(this,tr("¹§Ï²Äú"),tr("×¢²á³É¹¦£¬ÇëµÇÂ¼"),QMessageBox::Ok);
    //ui->lineEdit->clear();
    ui->lineEdit_5->clear();
    }

}

//µã²ËµÇÂ¼°´Å¥µÇÂ¼²Ù×÷
void login::on_pushButton_3_clicked()
{
    QString s;
    s=ui->lineEdit->text();
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("ÇëÊäÈëÊÖ»úºÅ"),
                                 tr("ÇëÏÈÊäÈëÊÖ»úºÅÔÙµÇÂ¼£¡Èç¹ûÃ»ÓÐ×¢²á£¬ÇëÏÈ×¢²á£¡"),QMessageBox::Ok);
        ui->lineEdit->setFocus();
    }
    else{
        if(s.length()!=11){QMessageBox::warning(this,tr("ÌáÊ¾"),tr("ÇëÊäÈëÒÑ¾­×¢²áµÄÊÖ»úºÅµÇÂ½£¡"),QMessageBox::Ok);
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
                QMessageBox::warning(this,tr("ÌáÊ¾"),tr("ÃÜÂë»òÕËºÅÄØ´íÎó£¡ÇëÖØÐÂÊäÈë¡£"),QMessageBox::Ok);
            }
        }

    }
    ui->lineEdit->clear();
    ui->lineEdit_5->clear();

}
//¹ÜÀíÏµÍ³µÇÂ¼°´Å¥
void login::on_pushButton_5_clicked()
{
    if(ui->lineEdit_2->text().isEmpty()){
        QMessageBox::information(this,tr("ÇëÊäÈëÃÜÂë "),
                                 tr("ÇëÏÈÊäÈëÃÜÂëµÇÂ¼"),QMessageBox::Ok);
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
           QMessageBox::warning(this, tr("ÃÜÂë´íÎó"), tr("ÃÜÂë´íÎó£¬ÇëÊäÈëÕýÈ·µÄÃÜÂëµÇÂ¼£¡"), QMessageBox::Ok);
               ui->lineEdit_2->clear();
                    ui->lineEdit_2->setFocus();
       }
    }
    //this->close();
}
//³øÊ¦µÇÂ¼
void login::on_pushButton_7_clicked()
{
    if(ui->lineEdit_3->text().isEmpty()){
        QMessageBox::information(this,tr("ÇëÊäÈëÃÜÂë"),tr("ÇëÊäÈë³øÊ¦ÃÜÂëµÇÂ¼"),QMessageBox::Ok);
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
            QMessageBox::warning(this,tr("ÃÜÂë´íÎó"),tr("ÃÜÂë´íÎó£¬ÇëÖØÐÂÊäÈë£¡"),QMessageBox::Ok);
            ui->lineEdit_3->clear();
            ui->lineEdit_3->setFocus();
        }
    }
}
//·þÎñÔ±µÇÂ¼
void login::on_pushButton_8_clicked()
{
    if(ui->lineEdit_4->text().isEmpty()){
        QMessageBox::information(this,tr("ÇëÊäÈëÃÜÂë"),tr("ÇëÊäÈë·þÎñÔ±ÃÜÂëµÇÂ¼"),QMessageBox::Ok);
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
            QMessageBox::warning(this,tr("ÃÜÂë´íÎó"),tr("ÃÜÂë´íÎó£¬ÇëÖØÐÂÊäÈë£¡"),QMessageBox::Ok);
            ui->lineEdit_4->clear();
            ui->lineEdit_4->setFocus();
        }
    }
}
//¾­ÀíµÇÂ¼
void login::on_pushButton_9_clicked()
{
    if(ui->lineEdit_6->text().isEmpty()){
        QMessageBox::information(this,tr("ÇëÊäÈëÃÜÂë"),tr("ÇëÊäÈë¾­ÀíÃÜÂëµÇÂ¼"),QMessageBox::Ok);
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
            QMessageBox::warning(this,tr("ÃÜÂë´íÎó"),tr("ÃÜÂë´íÎó£¬ÇëÖØÐÂÊäÈë£¡"),QMessageBox::Ok);
            ui->lineEdit_6->clear();
            ui->lineEdit_6->setFocus();
        }
    }
}
