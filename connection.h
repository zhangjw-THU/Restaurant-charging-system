#ifndef CAIDAN_H
#define CAIDAN_H
#include<QMessageBox>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QtSql>
static bool createConnection()
{
    //创建一个数据库连接
    QSqlDatabase db1=QSqlDatabase::addDatabase("QSQLITE");
    db1.setDatabaseName("my.db");
    db1.setPassword("123456");
    if(!db1.open()){
        QMessageBox::critical(0, "Cannot open database1 ",
                    "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db1);
    //创建菜单表caidan(不用了）
    query.exec(QString("create table caidan (id int primary key, "
             "name varchar not null,price int not null, info varchar)"));
    query.exec(QString("insert into caidan values(1,'开水',0,'免费')"));
    query.exec(QString("insert into caidan values(2,'回锅肉',12,'赞')"));
    query.exec(QString("insert into caidan values(3,'香干肉丝',12,'好吃')"));
    query.exec(QString("insert into caidan values(4,'咸鱼茄子',15,'好吃')"));
    query.exec(QString("insert into caidan values(5,'红烧肥肠',20,'好吃')"));


    //创建菜单表menu()
    query.exec(QString("create table mymenu (id int primary key, "
             "name varchar not null,ctype varchar,price int not null, info varchar)"));
    query.exec(QString("insert into mymenu values(1,'雪碧','饮品',10,'免费')"));
    query.exec(QString("insert into mymenu values(2,'回锅肉','肉类',12,'赞')"));
    query.exec(QString("insert into mymenu values(3,'红烧刀鱼','海鲜类',12,'好吃')"));
    query.exec(QString("insert into mymenu values(4,'香菇炒肉','青菜类',15,'好吃')"));
    query.exec(QString("insert into mymenu values(5,'小白菜排骨锅','锅类',20,'好吃')"));
    query.exec(QString("insert into mymenu values(6,'苜蓿瓜片汤','汤类',20,'好吃')"));
    query.exec(QString("insert into mymenu values(7,'黄瓜大拌','凉菜类',20,'好吃')"));
    query.exec(QString("insert into mymenu values(8,'拉面','主食',10,'好吃')"));
    //创建已点菜单表ydcaidan
    query.exec(QString("create table ydcaidan(id int primary key, "
                       "name varchar,num int,price int)"));
    //创建客户信息people(不用了)
    query.exec(QString("create table people(phonenumber varchar)"));
    query.exec(QString("insert into people values('18822556645')"));
    query.exec(QString("insert into people values('18825647532')"));
    query.exec(QString("insert into people values('18856984123')"));
    query.exec(QString("insert into people values('12547563245')"));
    //创建客户信息表cguest
    query.exec(QString("create table cguest(gid varchar,gpwd varchar)"));
    query.exec(QString("insert into cguest values('18811112222','00000'"));
    //user
    query.exec(QString("create table user(id varchar,pwd varchaer)"));
    //创建桌子+服务员信息serve（不用了）
    query.exec(QString("create table serve(tableid int primary key, "
                       "waitername varchar,guest varchar)"));
    query.exec(QString("insert into serve values(1,'张伟','没人')"));
    query.exec(QString("insert into serve values(2,'张三','没人')"));
    query.exec(QString("insert into serve values(3,'李四','没人')"));
    query.exec(QString("insert into serve values(4,'王明','没人')"));
    query.exec(QString("insert into serve values(5,'赵明','没人')"));
    query.exec(QString("insert into serve values(6,'刘亮','没人')"));
    query.exec(QString("insert into serve values(7,'郭佳','没人')"));
    query.exec(QString("insert into serve values(8,'杨峰','没人')"));
    //创建桌子+服务员信息waiter
    query.exec(QString("create table waiter(tableid int primary key, "
                       "name varchar,guest varchar)"));
    query.exec(QString("insert into waiter values(1,'张伟','没人')"));
    query.exec(QString("insert into waiter values(2,'张三','没人')"));
    query.exec(QString("insert into waiter values(3,'李四','没人')"));
    query.exec(QString("insert into waiter values(4,'王明','没人')"));
    query.exec(QString("insert into waiter values(5,'赵明','没人')"));
    query.exec(QString("insert into waiter values(6,'刘亮','没人')"));
    query.exec(QString("insert into waiter values(7,'郭佳','没人')"));
    query.exec(QString("insert into waiter values(8,'杨峰','没人')"));
    //创建顾客信息列表ginfo
    query.exec(QString("create table ginfo(info varchar)"));
    //创建厨师接单cmenu
    query.exec("create table cmenu(cid int primary key,"
               "cname varchar,cnum int,cstate varchar)");

    //创建管理员密码表password
    query.exec("create table password(pwd varchar primary key)");
        query.exec("insert into password values('123456')");

    //创建厨师密码表cpassword
        query.exec("create table cpassword(cpwd varchar primary key)");
            query.exec("insert into cpassword values('666666')");
    //创立服务员密码表wpassword
            query.exec("create table wpassword(wpwd varchar primary key)");
                query.exec("insert into wpassword values('888888')");
    //创建经理密码表
                query.exec("create table mpassword(mpwd varchar primary key)");
                    query.exec("insert into mpassword values('000000')");
                //创建分类表type
     query.exec("create table type(id int,name varchar)");
       query.exec(QString("insert into type values(1,'饮品')"));
                query.exec(QString("insert into type values(2,'肉类')"));
                query.exec(QString("insert into type values(3,'海鲜类')"));
                query.exec(QString("insert into type values(4,'青菜类')"));
                query.exec(QString("insert into type values(5,'锅类')"));
                query.exec(QString("insert into type values(6,'汤类')"));
                query.exec(QString("insert into type values(7,'凉菜类')"));
                query.exec(QString("insert into type values(8,'主食')"));
      //创建对服务员的评价
                query.exec("create table manageo(tableid int,name varchar,menunum int,winfo varchar)");
      //创建对厨师的评价
                query.exec("create table managet(menunum int,cinfo varchar)");

    return true;
}

#endif // CAIDAN_H
