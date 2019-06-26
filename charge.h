#ifndef CHARGE_H
#define CHARGE_H

#include <QDialog>

namespace Ui {
class charge;
}

class charge : public QDialog
{
    Q_OBJECT
    
public:
    explicit charge(QWidget *parent = 0);
    ~charge();
    

private:
    Ui::charge *ui;
};

#endif // CHARGE_H
