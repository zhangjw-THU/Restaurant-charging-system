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
    //�˵���ʾ
    model = new QSqlTableModel(this);
    model->setTable("mymenu");
    model->select();
    //���ñ༭����
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_3->setModel(model);

    //�ѵ�˵�
    ydmodel = new QSqlTableModel(this);
    ydmodel->setTable("ydcaidan");
    ydmodel->select();
    //���ñ༭����
    ydmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_4->setModel(ydmodel);
    //���ۺͽ���Ŀ¼
    advice = new QSqlTableModel(this);
    advice->setTable("ydcaidan");
    advice->select();

    advice->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_5->setModel(advice);
    //������ʾ
    table =new QSqlTableModel(this);
    table->setTable("waiter");
    table->select();
    table->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(table);
    //����
    tmodel=new QSqlQueryModel(this);
     //tmodel->setQuery("type");
    tmodel->setQuery(QString("select name from type"));
    ui->comboBox->setModel(tmodel);

}
guest::~guest()
{
    delete ui;
}
//���
void guest::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
//�ѵ�˵�
void guest::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
//�ͻ�����
void guest::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
//���
void guest::on_pushButton_14_clicked()
{
    //��ȡѡ����
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
    //�õ�ѡ���е�����
    query.exec(QString("select * from mymenu where id='%1'")
              .arg(idn));
    query.next();
   // idn=query.value(0).toInt();
    namen=query.value(1).toString();
    qDebug()<<query.value(1).toString();
    pricen=query.value(3).toDouble()*numn;
    qDebug()<<pricen;
    ydmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //��ʼ��ydcaidan�����޸�
    query.exec("select * from ydcaidan");
    //query.next();
    query.prepare(QString("insert into ydcaidan (id,name,num,price)values(:id,:name,:num,:price)"));
   query.bindValue(":id",idn);
    query.bindValue(":name",namen);
    query.bindValue(":num",numn);
    query.bindValue(":price",pricen);
    query.exec();
}
//ɾ��ѡ����
void guest::on_pushButton_13_clicked()
{
    int curRow = ui->tableView_4->currentIndex().row();
       // ɾ������
       ydmodel->removeRow(curRow);
       int ok = QMessageBox::warning(this,tr("ɾ����ݲ�!"),
                     tr("��ȷ��ɾ����ݲ�����"),QMessageBox::Yes, QMessageBox::No);
       if(ok == QMessageBox::No)
       { // �����ɾ��������
           ydmodel->revertAll();
       } else { // �����ύ�������ݿ���ɾ������
           ydmodel->submitAll();
       }
}
//ˢ�²˵���ť
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
//�ύ���۰�ť
void guest::on_pushButton_19_clicked()
{
    int idn=ui->spinBox_2->value();
    QString s;
    s=ui->lineEdit_2->text();
    QSqlQuery query;
    //�õ�ѡ���е�����
    query.exec(QString("select * from mymenu where id='%1'")
              .arg(idn));
    query.next();
    //�����۲���

    query.exec(QString("update mymenu set info = ('%1')where id=('%2')").arg(s).arg(idn));
    QMessageBox::information(this,"�ύ�ɹ�","лл�������ۣ�");
    ui->lineEdit_2->clear();
    ui->spinBox_2->clear();

}
//�û����˰�ťʱ�����ܽ��+����Ϣ��������Ա
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

    query.exec(QString("insert into ginfo(info) values('��')"));
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
//�˳���¼��ͬʱ����ѵ�˵����������
void guest::on_pushButton_7_clicked()
{

    QSqlQuery query;
    query.exec("delete from ydcaidan");
    query.exec("delete from cmenu");
    QMessageBox::information(this,"Thank you","лл������ѣ���ӭ�´ι��٣�");
    QMessageBox::information(this,"Thank you","�˳��ɹ���");
    this->close();
    login *l=new login;
    l->show();
    int i=ui->lineEdit_4->text().toInt();
    query.exec(QString("select * from waiter where tableid='%1'")
              .arg(i));
    query.next();
    query.exec(QString("update waiter set guest = 'û��' where tableid=('%1')").arg(i));


}
//�ύ������ť+���ѵ�˵�������ʦ
void guest::on_pushButton_17_clicked()
{

    QMessageBox megBox;
    megBox.setText("�⽫��������ղ˵�");
    megBox.setInformativeText("��ȷ���ύ��?");
    megBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    megBox.setDefaultButton(QMessageBox::Yes);
    int j=megBox.exec();
    if(j==QMessageBox::Yes)
    {ui->stackedWidget->setCurrentIndex(3);
    QString cnamen,cstaten;
    int cidn;
    int cnumn;
    cstaten="û��ʼ";
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
//ˢ�µĵĲ˵�
void guest::on_pushButton_8_clicked()
{
    advice->setTable("ydcaidan");
    advice->select();
    QSqlQuery query;
    query.exec(QString("select * from ydcaidan"));
}
//ѡ����λ
void guest::on_pushButton_6_clicked()
{
    int tablen=ui->spinBox_3->value();
    //i=tablen;
    QSqlQuery query;
    //query.seek(curRow);
    //�õ�ѡ���е�����
    query.exec(QString("select * from waiter where tableid='%1'")
              .arg(tablen));
    query.next();
    query.exec(QString("update waiter set guest = '�п���' where tableid=('%1')").arg(tablen));
    QMessageBox::information(this,"��ʾ","ѡ���ɹ���");
    table->setTable("waiter");
    table->select();
    ui->spinBox_3->clear();
    ui->lineEdit_4->setText(QString::number(tablen));
    ui->lineEdit_4->setReadOnly(true);
}
//�鿴����+ͬʱ�Ѳ˵��ӽ�ȥ
void guest::on_pushButton_9_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
     cmodel= new QSqlTableModel(this);
     cmodel->setTable("cmenu");
     cmodel->select();
     cmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
     ui->tableView_2->setModel(cmodel);


}
//ˢ�½���
void guest::on_pushButton_11_clicked()
{
    cmodel->setTable("cmenu");
    cmodel->select();
    QSqlQuery query;
    query.exec(QString("select * from cmenu"));

}
//�߲�
void guest::on_pushButton_10_clicked()
{
    QSqlQuery query;
    query.exec(QString("select * from ginfo"));
    //query.next();

    query.exec(QString("insert into ginfo(info) values('�˿ʹ߲�')"));
    query.exec();

}
//��ˮ
void guest::on_pushButton_12_clicked()
{
    QSqlQuery query;
    query.exec(QString("select * from ginfo"));
   // query.next();

    query.exec(QString("insert into ginfo(info) values('��ˮ')"));
    query.exec();
}

//����ѡ��
void guest::on_comboBox_activated(const QString &arg1)
{
    model->setFilter(QString("ctype = '%1'").arg(arg1));
    model->select();
}
//��ʾ���в�
void guest::on_pushButton_16_clicked()
{
    model->setTable("mymenu");
    model->select();
    ui->tableView_3->setModel(model);
}

//�Է���Ա�ύ����
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
//�Գ�ʦ�ύ����
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
