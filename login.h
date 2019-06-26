#ifndef LOGIN_H
#define LOGIN_H
#include"widget.h"
#include <QWidget>
#include"guest.h"
#include"waiter.h"
#include"chef.h"
class QSqlTableModel;
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT
    friend class guest;
public:
    explicit login(QWidget *parent = 0);

    //guest* g;waiter* w;
    //connect(g->ui,SIGNAL(g->on_pushButton_12_clicked()),w->ui,SLOT(w->messagejs()));


    ~login();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::login *ui;
    QSqlTableModel *model;


};

#endif // LOGIN_H
