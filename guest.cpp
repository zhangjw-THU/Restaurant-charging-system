#include "guest.h"
#include "ui_guest.h"
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
guest::guest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::guest)
{
    ui->setupUi(this);
    //菜单显示
    model = new QSqlTableModel(this);
    model->setTable("mymenu");
    model->select();
    //设置编辑策略
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_3->setModel(model);

    //已点菜单
    ydmodel = new QSqlTableModel(this);
    ydmodel->setTable("ydcaidan");
    ydmodel->select();
    //设置编辑策略
    ydmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_4->setModel(ydmodel);
    //评价和结账目录
    advice = new QSqlTableModel(this);
    advice->setTable("ydcaidan");
    advice->select();

    advice->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_5->setModel(advice);
    //桌子显示
    table =new QSqlTableModel(this);
    table->setTable("waiter");
    table->select();
    table->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(table);
    //类型
    tmodel=new QSqlQueryModel(this);
     //tmodel->setQuery("type");
    tmodel->setQuery(QString("select name from type"));
    ui->comboBox->setModel(tmodel);

}
guest::~guest()
{
    delete ui;
}
//点菜
void guest::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
//已点菜单
void guest::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
//客户评价
void guest::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
//点菜
void guest::on_pushButton_14_clicked()
{
    //获取选中行
    //int curRow=ui->tableView_3->currentIndex().row();
    QString idn,namen;
    int numn;
    double pricen;
    numn=ui->spinBox->value();
    idn=ui->lineEdit_3->text();
    ui->lineEdit_3->clear();
    ui->spinBox->clear();
    QSqlQuery query;
    //query.seek(curRow);
    //得到选中行的数据
    query.exec(QString("select * from mymenu where id='%1'")
              .arg(idn));
    query.next();
   // idn=query.value(0).toInt();
    namen=query.value(1).toString();
    qDebug()<<query.value(1).toString();
    pricen=query.value(3).toDouble()*numn;
    qDebug()<<pricen;
    ydmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //开始对ydcaidan进行修改
    query.exec("select * from ydcaidan");
    //query.next();
    query.prepare(QString("insert into ydcaidan (id,name,num,price)values(:id,:name,:num,:price)"));
   query.bindValue(":id",idn);
    query.bindValue(":name",namen);
    query.bindValue(":num",numn);
    query.bindValue(":price",pricen);
    query.exec();
}
//删除选中行
void guest::on_pushButton_13_clicked()
{
    int curRow = ui->tableView_4->currentIndex().row();
       // 删除该行
       ydmodel->removeRow(curRow);
       int ok = QMessageBox::warning(this,tr("删除这份菜!"),
                     tr("你确定删除这份菜吗吗？"),QMessageBox::Yes, QMessageBox::No);
       if(ok == QMessageBox::No)
       { // 如果不删除，则撤销
           ydmodel->revertAll();
       } else { // 否则提交，在数据库中删除该行
           ydmodel->submitAll();
       }
}
//刷新菜单按钮
void guest::on_pushButton_4_clicked()
{
    ydmodel->setTable("ydcaidan");
    ydmodel->select();
    QSqlQuery query;
    query.exec(QString("select * from ydcaidan"));
    while(query.next())
    {
    }


}
//提交评价按钮
void guest::on_pushButton_19_clicked()
{
    int idn=ui->spinBox_2->value();
    QString s;
    s=ui->lineEdit_2->text();
    QSqlQuery query;
    //得到选中行的数据
    query.exec(QString("select * from mymenu where id='%1'")
              .arg(idn));
    query.next();
    //把评价插入

    query.exec(QString("update mymenu set info = ('%1')where id=('%2')").arg(s).arg(idn));
    QMessageBox::information(this,"提交成功","谢谢您的评价！");
    ui->lineEdit_2->clear();
    ui->spinBox_2->clear();

}
//敲击结账按钮时计算总金额+见信息发给服务员
void guest::on_pushButton_20_clicked()
{
    ui->lineEdit->setEnabled(true);
    ui->lineEdit->setReadOnly(true);
    advice->setTable("ydcaidan");
    advice->select();
    QSqlQuery query;

   // QSqlQuery query;
    query.exec(QString("select * from ginfo"));
    //query.next();

    query.exec(QString("insert into ginfo(info) values('买单')"));
    query.exec();
    query.exec(QString("select * from ydcaidan"));
    double sum=0;


    while(query.next())
    {
        sum+=query.value(2).toDouble()*query.value(3).toDouble();
        qDebug()<<sum;
    }
    qDebug()<<sum;
    ui->lineEdit->setText(QString::number(sum));
}

void guest::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
//退出登录，同时清空已点菜单，清空桌子
void guest::on_pushButton_7_clicked()
{

    QSqlQuery query;
    query.exec("delete from ydcaidan");
    query.exec("delete from cmenu");
    QMessageBox::information(this,"Thank you","谢谢你的消费，欢迎下次光临！");
    QMessageBox::information(this,"Thank you","退出成功！");
    this->close();
    login *l=new login;
    l->show();
    int i=ui->lineEdit_4->text().toInt();
    query.exec(QString("select * from waiter where tableid='%1'")
              .arg(i));
    query.next();
    query.exec(QString("update waiter set guest = '没人' where tableid=('%1')").arg(i));


}
//提交订单按钮+把已点菜单传到厨师
void guest::on_pushButton_17_clicked()
{

    QMessageBox megBox;
    megBox.setText("这将是你的最终菜单");
    megBox.setInformativeText("你确定提交吗?");
    megBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    megBox.setDefaultButton(QMessageBox::Yes);
    int j=megBox.exec();
    if(j==QMessageBox::Yes)
    {ui->stackedWidget->setCurrentIndex(3);
    QString cnamen,cstaten;
    int cidn;
    int cnumn;
    cstaten="没开始";
    QSqlQuery query;
    QSqlQuery cquery;
    query.exec(QString("select * from ydcaidan"));
    while(query.next())
    {
        cidn=query.value(0).toInt();
        qDebug()<<"cidn:";
        qDebug()<<cidn;
        cnamen=query.value(1).toString();
        cnumn=query.value(2).toInt();
        bool q=cquery.exec(QString("select * from cmenu"));
        qDebug()<<q;
        cquery.next();
        bool p=cquery.prepare(QString("insert into cmenu (cid,cname,cnum,cstate)values(?,?,?,?)"));
        cquery.addBindValue(cidn);
        cquery.addBindValue(cnamen);
        cquery.addBindValue(cnumn);
        cquery.addBindValue(cstaten);
        cquery.exec();


    }
    query.exec(QString("select * from ydcaidan"));
    double sum=0;
    while(query.next())
    {
        sum+=query.value(2).toDouble()*query.value(3).toDouble();
        qDebug()<<sum;
    }
    qDebug()<<sum;
    ui->lineEdit->setText(QString::number(sum));
    }
}
//刷新的的菜单
void guest::on_pushButton_8_clicked()
{
    advice->setTable("ydcaidan");
    advice->select();
    QSqlQuery query;
    query.exec(QString("select * from ydcaidan"));
}
//选择座位
void guest::on_pushButton_6_clicked()
{
    int tablen=ui->spinBox_3->value();
    //i=tablen;
    QSqlQuery query;
    //query.seek(curRow);
    //得到选中行的数据
    query.exec(QString("select * from waiter where tableid='%1'")
              .arg(tablen));
    query.next();
    query.exec(QString("update waiter set guest = '有客人' where tableid=('%1')").arg(tablen));
    QMessageBox::information(this,"提示","选座成功！");
    table->setTable("waiter");
    table->select();
    ui->spinBox_3->clear();
    ui->lineEdit_4->setText(QString::number(tablen));
    ui->lineEdit_4->setReadOnly(true);
}
//查看进度+同时把菜单加进去
void guest::on_pushButton_9_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
     cmodel= new QSqlTableModel(this);
     cmodel->setTable("cmenu");
     cmodel->select();
     cmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
     ui->tableView_2->setModel(cmodel);


}
//刷新进度
void guest::on_pushButton_11_clicked()
{
    cmodel->setTable("cmenu");
    cmodel->select();
    QSqlQuery query;
    query.exec(QString("select * from cmenu"));

}
//催菜
void guest::on_pushButton_10_clicked()
{
    QSqlQuery query;
    query.exec(QString("select * from ginfo"));
    //query.next();

    query.exec(QString("insert into ginfo(info) values('顾客催菜')"));
    query.exec();

}
//加水
void guest::on_pushButton_12_clicked()
{
    QSqlQuery query;
    query.exec(QString("select * from ginfo"));
   // query.next();

    query.exec(QString("insert into ginfo(info) values('加水')"));
    query.exec();
}

//类型选择
void guest::on_comboBox_activated(const QString &arg1)
{
    model->setFilter(QString("ctype = '%1'").arg(arg1));
    model->select();
}
//显示所有菜
void guest::on_pushButton_16_clicked()
{
    model->setTable("mymenu");
    model->select();
    ui->tableView_3->setModel(model);
}

//对服务员提交评价
void guest::on_pushButton_15_clicked()
{
    int idn,numn;
    QString namen,winfon;
    idn=ui->lineEdit_4->text().toInt();
    QSqlQuery query;
    query.exec(QString("select * from waiter where tableid='%1'").arg(idn));
    query.next();
    namen=query.value(1).toString();
    query.exec("select * from cmenu");
    query.last();
    numn=query.at()+1;
    winfon=ui->lineEdit_5->text();
    ui->lineEdit_5->clear();
    query.exec("select * from manageo");
    query.exec(QString("insert into manageo (tableid,name,menunum,winfo) values (?,?,?,?)"));
    query.addBindValue(idn);
    query.addBindValue(namen);
    query.addBindValue(numn);
    query.addBindValue(winfon);
    query.exec();
}
//对厨师提交评价
void guest::on_pushButton_18_clicked()
{
    int numn;
    QString cinfon;
     QSqlQuery query;
    query.exec("select * from cmenu");
    query.last();
    numn=query.at()+1;
    cinfon=ui->lineEdit_6->text();
    ui->lineEdit_6->clear();
    query.exec("select * from managet");
    query.exec(QString("insert into managet(menunum,cinfo)values(?,?)"));
    query.addBindValue(numn);
    query.addBindValue(cinfon);
    query.exec();

}
