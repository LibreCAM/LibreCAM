#include "camprofilewidget.h"
#include "ui_camprofilewidget.h"

CAMProfileWidget::CAMProfileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CAMProfileWidget)
{
    ui->setupUi(this);
}

CAMProfileWidget::~CAMProfileWidget()
{
    delete ui;
}
