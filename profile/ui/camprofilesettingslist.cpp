#include "profile/ui/camprofilesettingslist.h"
#include "ui_camprofilesettingslist.h"
#include "profile/src/camprofiledata.h"
#include "profile/src/camprofiledataparser.h"
#include "profile/ui/camprofilesettings.h"

#include <QDir>
#include <QDesktopServices>
#include <QListIterator>
#include <QLocale>


CAMProfileSettingsList::CAMProfileSettingsList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAMProfileSettingsList)
{
    ui->setupUi(this);
    camProfileDataModel=new CAMProfileDataModel();
    ui->tableView->setModel(camProfileDataModel);
    loadPreferences();
    ui->tableView->resizeColumnsToContents();
}

CAMProfileSettingsList::~CAMProfileSettingsList()
{
    delete camProfileDataModel;
    delete ui;
}

/**
  * TODO: Use a stream writer
  *
  */
void CAMProfileSettingsList::savePreferences() {
    QString location = "profile.xml";
            /*QStandardPaths::DesktopLocation(
                QStandardPaths::DocumentsLocation) +
            QDir::separator() + "rvtcam" + QDir::separator() + "profile.xml";*/

    QFile file(location);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QDomDocument document;
        QDomElement root = document.createElement( "root" );
        QDomElement eCAMProfileDataList = document.createElement( "CAMProfileDataList" );

        document.appendChild(root);
        root.appendChild(eCAMProfileDataList);

        QListIterator<CAMProfileData *>  i(camProfileDataModel->getList());
        while (i.hasNext()) {
            CAMProfileData *cpd=i.next();
            QDomElement e=cpd->getDomElement(&document);
            eCAMProfileDataList.appendChild(e);
        }
        QTextStream out(&file);
        out << document.toString();
        file.close();
    }
}

/**
  * TODO: Use a stream reader
  *
  */
void CAMProfileSettingsList::loadPreferences() {
    QString location = "profile.xml";
            //QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation) + QDir::separator() + "rvtcam" + QDir::separator() + "profile.xml";

    QFile file(location);
    if (file.open(QIODevice::ReadOnly)) {
        camProfileDataModel->clear();
        CAMProfileDataParser parser(camProfileDataModel);
        QXmlSimpleReader reader;
        reader.setContentHandler(&parser);
        QXmlInputSource xmlInputSource(&file);
        reader.parse(xmlInputSource);
    }
    file.close();
}

/**
  * Delete the given profile preference
  *
  */
void CAMProfileSettingsList::on_bDelete_clicked() {
    // Get all selections
   QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();

   QList<int> list;
   for (int i = 0; i < indexes.count(); ++i)
   {
       list.append(indexes.at(i).row());
   }

   list=QSet<int>::fromList(list).toList();
   qSort(list.begin(), list.end());
   while (!list.empty()) {
       camProfileDataModel->removeRows(list.takeLast(),1);
   }
   savePreferences();
   ui->tableView->resizeColumnsToContents();

}

/**
  * Edit selected profile preferences
  *
  *
  */
void CAMProfileSettingsList::on_bEdit_clicked(const QModelIndex &parent) {
    Q_UNUSED(parent);
    //ui->tableView->selectedItems();

     // Get all selections
    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();

    QList<int> list;
    for (int i = 0; i < indexes.count(); ++i)
    {
        list.append(indexes.at(i).row());
    }
    list=QSet<int>::fromList(list).toList();
    foreach(int row, list)
    {
        CAMProfileSettings cps(this);
        cps.setData(camProfileDataModel->getList().at(row));
        if (cps.exec()==QDialog::Accepted) {
            savePreferences();
        }
    }
    ui->tableView->resizeColumnsToContents();

}

void CAMProfileSettingsList::on_bAdd_clicked() {
    CAMProfileSettings cps(this);
    CAMProfileData *cpd=new CAMProfileData();
    cps.setData(cpd);
    if (cps.exec()==QDialog::Accepted) {
        this->camProfileDataModel->addProfileData(cpd);
        savePreferences();
    } else {
        delete cpd;
    }
    ui->tableView->resizeColumnsToContents();

}

void CAMProfileSettingsList::scloseDialog() {
    this->accept();
}
