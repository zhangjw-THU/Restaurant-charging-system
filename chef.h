#ifndef CHEF_H
#define CHEF_H

#include <QDialog>
class QSqlTableModel;

namespace Ui {
class chef;
}

class chef : public QDialog
{
    Q_OBJECT
    
public:
    explicit chef(QWidget *parent = 0);
    ~chef();
    
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::chef *ui;
    QSqlTableModel *cmodel;
};

#endif // CHEF_H
