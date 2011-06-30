#include "jhallwidget.h"
#include "ui_jhallwidget.h"

JHallWidget::JHallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JHallWidget)
{
    ui->setupUi(this);
}

JHallWidget::~JHallWidget()
{
    delete ui;
}
