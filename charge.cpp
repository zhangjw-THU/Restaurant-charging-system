#include "charge.h"
#include "ui_charge.h"

charge::charge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::charge)
{
    ui->setupUi(this);
}

charge::~charge()
{
    delete ui;
}
