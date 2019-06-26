#include "widget.h"
#include"login.h"
#include "ui_widget.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include"connection.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("mymenu");
    model->select();
        // 设置编辑策略
   // QTableView *view=new QTableView(this);
    //view->setModel(model);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);

    phone = new QSqlTableModel(this);
    phone->setTable("cguest");
    phone->select();
    phone->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_2->setModel(phone);
    //餐桌显示
    cmodel =new QSqlTableModel(this);
    cmodel->setTable("waiter");
    cmodel->select();
    cmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_3->setModel(cmodel);

    //类型显示
    tmodel=new QSqlQueryModel(this);
     //tmodel->setQuery("type");
    tmodel->setQuery(QString("select name from type"));
    ui->comboBox->setModel(tmodel);

}

Widget::~Widget()
{
    delete ui;
}
//修改按钮
void Widget::on_pushButton_3_clicked()
{
    model->database().transaction();
    if(model->submitAll()){
        model->database().commit();
    }else{
        model->database().rollback();
        QMessageBox::warning(this,tr("tableModel"),
                             tr("数据错误: %1").arg(model->lastError().text()));

    }
}//撤销修改
void Widget::on_pushButton_9_clicked()
{
     model->revertAll();
}
//查询
void Widget::on_pushButton_10_clicked()
{
    QString name = ui->lineEdit->text();
        //根据姓名进行筛选，一定要使用单引号
        model->setFilter(QString("name = '%1'").arg(name));
        model->select();
}
//显示全部菜单
void Widget::on_pushButton_8_clicked()
{
    model->setTable("mymenu");
        model->select();
}
//删除选中按钮

void Widget::on_pushButton_7_clicked()
{
    // 获取选中的行
        int curRow = ui->tableView->currentIndex().row();
        // 删除该行
        model->removeRow(curRow);
        int ok = QMessageBox::warning(this,tr("删除当前行!"),
                      tr("你确定删除当前行吗？"),QMessageBox::Yes, QMessageBox::No);
        if(ok == QMessageBox::No)
        { // 如果不删除，则撤销
            model->revertAll();
        } else { // 否则提交，在数据库中删除该行
            model->submitAll();
        }
}
//添加菜品
void Widget::on_pushButton_4_clicked()
{
    // 获得表的行数
        int rowNum = model->rowCount();
        int id = 10;
        // 添加一行
        model->insertRow(rowNum);
        model->setData(model->index(rowNum,0), id);
        // 可以直接提交
        //model->submitAll();
}
//手机号查询
void Widget::on_pushButton_18_clicked()
{
    QString phonenumber = ui->lineEdit_2->text();
        //根据手机号进行筛选，一定要使用单引号
        phone->setFilter(QString("phonenumber = '%1'").arg(phonenumber));
        phone->select();
}
//显示所有手机号
void Widget::on_pushButton_16_clicked()
{
    ui->lineEdit_2->clear();
    phone->setTable("cguest");
        phone->select();
}
//删除选中行
void Widget::on_pushButton_15_clicked()
{
    // 获取选中的行
        int curRow = ui->tableView_2->currentIndex().row();
        // 删除该行
        phone->removeRow(curRow);
        int ok = QMessageBox::warning(this,tr("删除当前行!"),
                      tr("你确定删除当前行吗？"),QMessageBox::Yes, QMessageBox::No);
        if(ok == QMessageBox::No)
        { // 如果不删除，则撤销
            phone->revertAll();
        } else { // 否则提交，在数据库中删除该行
            phone->submitAll();
        }
}
//提交修改
void Widget::on_pushButton_11_clicked()
{
    phone->database().transaction();
    if(phone->submitAll()){
        phone->database().commit();
    }else{
        phone->database().rollback();
        QMessageBox::warning(this,tr("tableModel"),
                             tr("数据错误: %1").arg(phone->lastError().text()));

    }
}

//敲菜单管理按钮
void Widget::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
//敲击客户管理按钮

void Widget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
//退出登录
void Widget::on_pushButton_5_clicked()
{
    QMessageBox::information(this,"Thank you","退出成功！");
    this->close();
    login *l=new login;
    l->show();
}
//挑选
void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    model->setFilter(QString("ctype = '%1'").arg(arg1));
    model->select();
}
//显示餐桌修改
void Widget::on_pushButton_6_clicked()
{
   ui->stackedWidget->setCurrentIndex(2);
}
//添加餐桌
void Widget::on_pushButton_12_clicked()
{
    // 获得表的行数
        int rowNum = cmodel->rowCount();
        int id = 10;
        // 添加一行
        cmodel->insertRow(rowNum);
        cmodel->setData(cmodel->index(rowNum,0), id);
        // 可以直接提交
        //model->submitAll();
}
//删除餐桌
void Widget::on_pushButton_13_clicked()
{
    // 获取选中的行
        int curRow = ui->tableView_3->currentIndex().row();
        // 删除该行
        cmodel->removeRow(curRow);
        int ok = QMessageBox::warning(this,tr("删除当前行!"),
                      tr("你确定删除当前餐桌吗？"),QMessageBox::Yes, QMessageBox::No);
        if(ok == QMessageBox::No)
        { // 如果不删除，则撤销
            cmodel->revertAll();
        } else { // 否则提交，在数据库中删除该行
            cmodel->submitAll();
        }
}
//提交修改
void Widget::on_pushButton_14_clicked()
{
    cmodel->database().transaction();
    if(cmodel->submitAll()){
        cmodel->database().commit();
    }else{
        cmodel->database().rollback();
        QMessageBox::warning(this,tr("tableModel"),
                             tr("数据错误: %1").arg(phone->lastError().text()));

    }
}
//撤销修改
void Widget::on_pushButton_17_clicked()
{
    cmodel->revertAll();
}
