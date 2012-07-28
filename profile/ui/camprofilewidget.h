#ifndef CAMPROFILEWIDGET_H
#define CAMPROFILEWIDGET_H

#include <QWidget>

namespace Ui {
    class CAMProfileWidget;
}

class CAMProfileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CAMProfileWidget(QWidget *parent = 0);
    ~CAMProfileWidget();

private:
    Ui::CAMProfileWidget *ui;
};

#endif // CAMProfileWidget_H
