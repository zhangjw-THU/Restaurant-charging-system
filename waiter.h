#ifndef WAITER_H
#define WAITER_H

#include <QDialog>
class QSqlTableModel;
namespace Ui {
class waiter;
}

class waiter : public QDialog
{
    Q_OBJECT
    
public:
    explicit waiter(QWidget *parent = 0);
    ~waiter();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::waiter *ui;
    QSqlTableModel *model;
    QSqlTableModel *amodel;
    QSqlTableModel *bmodel;

};

#endif // WAITER_H
