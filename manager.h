#ifndef MANAGER_H
#define MANAGER_H

#include <QDialog>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlQueryModel>
class QSqlTableModel;
namespace Ui {
class manager;
}

class manager : public QDialog
{
    Q_OBJECT
    
public:
    explicit manager(QWidget *parent = 0);
    ~manager();
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::manager *ui;
    QSqlTableModel *modelo;
    QSqlTableModel *modelt;
};

#endif // MANAGER_H
