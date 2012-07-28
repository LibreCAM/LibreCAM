#include "CAMProfileWidget.h"
#include "ui_CAMProfileWidget.h"

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
