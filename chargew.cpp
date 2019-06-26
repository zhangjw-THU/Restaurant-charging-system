#include "chargew.h"
#include "ui_chargew.h"

chargew::chargew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chargew)
{
    ui->setupUi(this);
}

chargew::~chargew()
{
    delete ui;
}
