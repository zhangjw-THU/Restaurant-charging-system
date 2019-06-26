#ifndef CAIDAN_H
#define CAIDAN_H
#include<QMessageBox>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QtSql>
static bool createConnection()
{
    //����һ�����ݿ�����
    QSqlDatabase db1=QSqlDatabase::addDatabase("QSQLITE");
    db1.setDatabaseName("my.db");
    db1.setPassword("123456");
    if(!db1.open()){
        QMessageBox::critical(0, "Cannot open database1 ",
                    "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db1);
    //�����˵���caidan(�����ˣ�
    query.exec(QString("create table caidan (id int primary key, "
             "name varchar not null,price int not null, info varchar)"));
    query.exec(QString("insert into caidan values(1,'��ˮ',0,'���')"));
    query.exec(QString("insert into caidan values(2,'�ع���',12,'��')"));
    query.exec(QString("insert into caidan values(3,'�����˿',12,'�ó�')"));
    query.exec(QString("insert into caidan values(4,'��������',15,'�ó�')"));
    query.exec(QString("insert into caidan values(5,'���շʳ�',20,'�ó�')"));


    //�����˵���menu()
    query.exec(QString("create table mymenu (id int primary key, "
             "name varchar not null,ctype varchar,price int not null, info varchar)"));
    query.exec(QString("insert into mymenu values(1,'ѩ��','��Ʒ',10,'���')"));
    query.exec(QString("insert into mymenu values(2,'�ع���','����',12,'��')"));
    query.exec(QString("insert into mymenu values(3,'���յ���','������',12,'�ó�')"));
    query.exec(QString("insert into mymenu values(4,'�㹽����','�����',15,'�ó�')"));
    query.exec(QString("insert into mymenu values(5,'С�ײ��Źǹ�','����',20,'�ó�')"));
    query.exec(QString("insert into mymenu values(6,'��ޣ��Ƭ��','����',20,'�ó�')"));
    query.exec(QString("insert into mymenu values(7,'�ƹϴ��','������',20,'�ó�')"));
    query.exec(QString("insert into mymenu values(8,'����','��ʳ',10,'�ó�')"));
    //�����ѵ�˵���ydcaidan
    query.exec(QString("create table ydcaidan(id int primary key, "
                       "name varchar,num int,price int)"));
    //�����ͻ���Ϣpeople(������)
    query.exec(QString("create table people(phonenumber varchar)"));
    query.exec(QString("insert into people values('18822556645')"));
    query.exec(QString("insert into people values('18825647532')"));
    query.exec(QString("insert into people values('18856984123')"));
    query.exec(QString("insert into people values('12547563245')"));
    //�����ͻ���Ϣ��cguest
    query.exec(QString("create table cguest(gid varchar,gpwd varchar)"));
    query.exec(QString("insert into cguest values('18811112222','00000'"));
    //user
    query.exec(QString("create table user(id varchar,pwd varchaer)"));
    //��������+����Ա��Ϣserve�������ˣ�
    query.exec(QString("create table serve(tableid int primary key, "
                       "waitername varchar,guest varchar)"));
    query.exec(QString("insert into serve values(1,'��ΰ','û��')"));
    query.exec(QString("insert into serve values(2,'����','û��')"));
    query.exec(QString("insert into serve values(3,'����','û��')"));
    query.exec(QString("insert into serve values(4,'����','û��')"));
    query.exec(QString("insert into serve values(5,'����','û��')"));
    query.exec(QString("insert into serve values(6,'����','û��')"));
    query.exec(QString("insert into serve values(7,'����','û��')"));
    query.exec(QString("insert into serve values(8,'���','û��')"));
    //��������+����Ա��Ϣwaiter
    query.exec(QString("create table waiter(tableid int primary key, "
                       "name varchar,guest varchar)"));
    query.exec(QString("insert into waiter values(1,'��ΰ','û��')"));
    query.exec(QString("insert into waiter values(2,'����','û��')"));
    query.exec(QString("insert into waiter values(3,'����','û��')"));
    query.exec(QString("insert into waiter values(4,'����','û��')"));
    query.exec(QString("insert into waiter values(5,'����','û��')"));
    query.exec(QString("insert into waiter values(6,'����','û��')"));
    query.exec(QString("insert into waiter values(7,'����','û��')"));
    query.exec(QString("insert into waiter values(8,'���','û��')"));
    //�����˿���Ϣ�б�ginfo
    query.exec(QString("create table ginfo(info varchar)"));
    //������ʦ�ӵ�cmenu
    query.exec("create table cmenu(cid int primary key,"
               "cname varchar,cnum int,cstate varchar)");

    //��������Ա�����password
    query.exec("create table password(pwd varchar primary key)");
        query.exec("insert into password values('123456')");

    //������ʦ�����cpassword
        query.exec("create table cpassword(cpwd varchar primary key)");
            query.exec("insert into cpassword values('666666')");
    //��������Ա�����wpassword
            query.exec("create table wpassword(wpwd varchar primary key)");
                query.exec("insert into wpassword values('888888')");
    //�������������
                query.exec("create table mpassword(mpwd varchar primary key)");
                    query.exec("insert into mpassword values('000000')");
                //���������type
     query.exec("create table type(id int,name varchar)");
       query.exec(QString("insert into type values(1,'��Ʒ')"));
                query.exec(QString("insert into type values(2,'����')"));
                query.exec(QString("insert into type values(3,'������')"));
                query.exec(QString("insert into type values(4,'�����')"));
                query.exec(QString("insert into type values(5,'����')"));
                query.exec(QString("insert into type values(6,'����')"));
                query.exec(QString("insert into type values(7,'������')"));
                query.exec(QString("insert into type values(8,'��ʳ')"));
      //�����Է���Ա������
                query.exec("create table manageo(tableid int,name varchar,menunum int,winfo varchar)");
      //�����Գ�ʦ������
                query.exec("create table managet(menunum int,cinfo varchar)");

    return true;
}

#endif // CAIDAN_H
