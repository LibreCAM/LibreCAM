#ifndef CAMProfileSettings_H
#define CAMProfileSettings_H

#include <QDialog>

class CAMProfileData;

namespace Ui {
    class CAMProfileSettings;
}

class CAMProfileSettings : public QDialog
{
    Q_OBJECT

public:
    explicit CAMProfileSettings(QWidget *parent = 0, QList<CAMProfileData *> *camProfileDataList=0);
    ~CAMProfileSettings();

    void setData(CAMProfileData *cpd);
    CAMProfileData *getData();

private slots:
    void on_bCancel_clicked();
    void on_bOk_clicked();
    void testForm(QString);

private:
    Ui::CAMProfileSettings *ui;
    QList<CAMProfileData *> *camProfileDataList;
    CAMProfileData *camProfileData;
};

#endif // CAMProfileSettings_H
