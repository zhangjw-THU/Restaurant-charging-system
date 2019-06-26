#include "stackedwidget.h"
#include "ui_stackedwidget.h"

StackedWidget::StackedWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::StackedWidget)
{
    ui->setupUi(this);
}

StackedWidget::~StackedWidget()
{
    delete ui;
}
