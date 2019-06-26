#ifndef CHARGEW_H
#define CHARGEW_H

#include <QDialog>

namespace Ui {
class chargew;
}

class chargew : public QDialog
{
    Q_OBJECT
    
public:
    explicit chargew(QWidget *parent = 0);
    ~chargew();
    
private:
    Ui::chargew *ui;
};

#endif // CHARGEW_H
