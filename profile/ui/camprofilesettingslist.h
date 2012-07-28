#ifndef CAMPROFILESETTINGSLIST_H
#define CAMPROFILESETTINGSLIST_H

#include <QDialog>
#include <QModelIndex>

class CAMProfileDataModel;

namespace Ui {
    class CAMProfileSettingsList;
}

class CAMProfileSettingsList : public QDialog
{
    Q_OBJECT

public:
    explicit CAMProfileSettingsList(QWidget *parent = 0);
    ~CAMProfileSettingsList();

private:
    Ui::CAMProfileSettingsList *ui;


    void loadPreferences();
    void savePreferences();

private slots:
    void on_bAdd_clicked();
    void on_bEdit_clicked(const QModelIndex &parent=QModelIndex());
    void on_bDelete_clicked();
    void scloseDialog();

private:
    CAMProfileDataModel *camProfileDataModel;

};




#endif // CAMPROFILESETTINGSLIST_H
