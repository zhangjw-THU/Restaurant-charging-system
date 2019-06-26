#ifndef GUEST_H
#define GUEST_H

#include <QDialog>
#include"login.h"
#include<QSqlQueryModel>
class QSqlTableModel;

namespace Ui {
class guest;
}

class guest : public QDialog
{
    Q_OBJECT
    //friend class login;
public:
     //static int i;//用于记录桌子号
    explicit guest(QWidget *parent = 0);
    ~guest();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();


    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_16_clicked();

    void on_pushButton_15_clicked();


    void on_pushButton_18_clicked();

private:
    Ui::guest *ui;
    QSqlTableModel *model;
    QSqlTableModel *ydmodel;
    QSqlTableModel *advice;
    QSqlTableModel *table;
    QSqlTableModel *cmodel;
    QSqlQueryModel *tmodel;

};

#endif // GUEST_H


