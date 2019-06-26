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
        // ���ñ༭����
   // QTableView *view=new QTableView(this);
    //view->setModel(model);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);

    phone = new QSqlTableModel(this);
    phone->setTable("cguest");
    phone->select();
    phone->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_2->setModel(phone);
    //������ʾ
    cmodel =new QSqlTableModel(this);
    cmodel->setTable("waiter");
    cmodel->select();
    cmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_3->setModel(cmodel);

    //������ʾ
    tmodel=new QSqlQueryModel(this);
     //tmodel->setQuery("type");
    tmodel->setQuery(QString("select name from type"));
    ui->comboBox->setModel(tmodel);

}

Widget::~Widget()
{
    delete ui;
}
//�޸İ�ť
void Widget::on_pushButton_3_clicked()
{
    model->database().transaction();
    if(model->submitAll()){
        model->database().commit();
    }else{
        model->database().rollback();
        QMessageBox::warning(this,tr("tableModel"),
                             tr("���ݴ���: %1").arg(model->lastError().text()));

    }
}//�����޸�
void Widget::on_pushButton_9_clicked()
{
     model->revertAll();
}
//��ѯ
void Widget::on_pushButton_10_clicked()
{
    QString name = ui->lineEdit->text();
        //������������ɸѡ��һ��Ҫʹ�õ�����
        model->setFilter(QString("name = '%1'").arg(name));
        model->select();
}
//��ʾȫ���˵�
void Widget::on_pushButton_8_clicked()
{
    model->setTable("mymenu");
        model->select();
}
//ɾ��ѡ�а�ť

void Widget::on_pushButton_7_clicked()
{
    // ��ȡѡ�е���
        int curRow = ui->tableView->currentIndex().row();
        // ɾ������
        model->removeRow(curRow);
        int ok = QMessageBox::warning(this,tr("ɾ����ǰ��!"),
                      tr("��ȷ��ɾ����ǰ����"),QMessageBox::Yes, QMessageBox::No);
        if(ok == QMessageBox::No)
        { // �����ɾ��������
            model->revertAll();
        } else { // �����ύ�������ݿ���ɾ������
            model->submitAll();
        }
}
//��Ӳ�Ʒ
void Widget::on_pushButton_4_clicked()
{
    // ��ñ������
        int rowNum = model->rowCount();
        int id = 10;
        // ���һ��
        model->insertRow(rowNum);
        model->setData(model->index(rowNum,0), id);
        // ����ֱ���ύ
        //model->submitAll();
}
//�ֻ��Ų�ѯ
void Widget::on_pushButton_18_clicked()
{
    QString phonenumber = ui->lineEdit_2->text();
        //�����ֻ��Ž���ɸѡ��һ��Ҫʹ�õ�����
        phone->setFilter(QString("phonenumber = '%1'").arg(phonenumber));
        phone->select();
}
//��ʾ�����ֻ���
void Widget::on_pushButton_16_clicked()
{
    ui->lineEdit_2->clear();
    phone->setTable("cguest");
        phone->select();
}
//ɾ��ѡ����
void Widget::on_pushButton_15_clicked()
{
    // ��ȡѡ�е���
        int curRow = ui->tableView_2->currentIndex().row();
        // ɾ������
        phone->removeRow(curRow);
        int ok = QMessageBox::warning(this,tr("ɾ����ǰ��!"),
                      tr("��ȷ��ɾ����ǰ����"),QMessageBox::Yes, QMessageBox::No);
        if(ok == QMessageBox::No)
        { // �����ɾ��������
            phone->revertAll();
        } else { // �����ύ�������ݿ���ɾ������
            phone->submitAll();
        }
}
//�ύ�޸�
void Widget::on_pushButton_11_clicked()
{
    phone->database().transaction();
    if(phone->submitAll()){
        phone->database().commit();
    }else{
        phone->database().rollback();
        QMessageBox::warning(this,tr("tableModel"),
                             tr("���ݴ���: %1").arg(phone->lastError().text()));

    }
}

//�ò˵�����ť
void Widget::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
//�û��ͻ�����ť

void Widget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
//�˳���¼
void Widget::on_pushButton_5_clicked()
{
    QMessageBox::information(this,"Thank you","�˳��ɹ���");
    this->close();
    login *l=new login;
    l->show();
}
//��ѡ
void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    model->setFilter(QString("ctype = '%1'").arg(arg1));
    model->select();
}
//��ʾ�����޸�
void Widget::on_pushButton_6_clicked()
{
   ui->stackedWidget->setCurrentIndex(2);
}
//��Ӳ���
void Widget::on_pushButton_12_clicked()
{
    // ��ñ������
        int rowNum = cmodel->rowCount();
        int id = 10;
        // ���һ��
        cmodel->insertRow(rowNum);
        cmodel->setData(cmodel->index(rowNum,0), id);
        // ����ֱ���ύ
        //model->submitAll();
}
//ɾ������
void Widget::on_pushButton_13_clicked()
{
    // ��ȡѡ�е���
        int curRow = ui->tableView_3->currentIndex().row();
        // ɾ������
        cmodel->removeRow(curRow);
        int ok = QMessageBox::warning(this,tr("ɾ����ǰ��!"),
                      tr("��ȷ��ɾ����ǰ������"),QMessageBox::Yes, QMessageBox::No);
        if(ok == QMessageBox::No)
        { // �����ɾ��������
            cmodel->revertAll();
        } else { // �����ύ�������ݿ���ɾ������
            cmodel->submitAll();
        }
}
//�ύ�޸�
void Widget::on_pushButton_14_clicked()
{
    cmodel->database().transaction();
    if(cmodel->submitAll()){
        cmodel->database().commit();
    }else{
        cmodel->database().rollback();
        QMessageBox::warning(this,tr("tableModel"),
                             tr("���ݴ���: %1").arg(phone->lastError().text()));

    }
}
//�����޸�
void Widget::on_pushButton_17_clicked()
{
    cmodel->revertAll();
}
