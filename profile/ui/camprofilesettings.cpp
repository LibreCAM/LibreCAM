#include "camprofilesettings.h"
#include "profile/src/camprofiledata.h"
#include "ui_camprofilesettings.h"

#include <QMessageBox>
#include <QValidator>
#include <QDoubleValidator>

CAMProfileSettings::CAMProfileSettings(QWidget *parent, QList<CAMProfileData *> *camProfileDataList) :
    QDialog(parent),
    ui(new Ui::CAMProfileSettings)
{
    camProfileData=0;
    ui->setupUi(this);

    this->ui->leFeedCutRate->setValidator(new QDoubleValidator(0.1,1000000.0,4,this));
    this->ui->leFeedPlungeRate->setValidator(new QDoubleValidator(0.1,100000.0,4,this));

    this->ui->leFirstIncrement->setValidator(new QDoubleValidator(0.0,100.0,4,this));
    this->ui->leLastIncrement->setValidator(new QDoubleValidator(0.0,100.0,4,this));
    this->ui->leDepthIncrement->setValidator(new QDoubleValidator(0.0,1000.0,4,this));
    this->ui->leTargetDepth->setValidator(new QDoubleValidator(0.0,1000.0,4,this));

    this->ui->leOPName->setValidator(new QRegExpValidator(QRegExp(".+"),this));

    this->ui->leSavetyMargin->setValidator(new QDoubleValidator(0.0,1000.0,4,this));
    this->ui->leZRetract->setValidator(new QDoubleValidator(0.0,1000.0,4,this));

    this->ui->leSpindleRPM->setValidator(new QIntValidator(1,100000,this));

    this->ui->leToolDiameter->setValidator(new QDoubleValidator(0.0,250.0,4,this));
    this->ui->leToolNumber->setValidator(new QIntValidator(0,100,this));

    if (camProfileDataList==0)
        this->ui->bFindProfileOperation->hide();

}

CAMProfileSettings::~CAMProfileSettings()
{
    delete ui;
}

void CAMProfileSettings::setData( CAMProfileData *cpd) {

    camProfileData=cpd;
    QLocale locale;
    this->ui->leFeedCutRate->setText(locale.toString(cpd->feedCutRate,'f', 4));
    this->ui->leFeedPlungeRate->setText(locale.toString(cpd->feedPlungeRate,'f', 4));

    this->ui->leFirstIncrement->setText(locale.toString(cpd->firstIncrement,'f', 4));
    this->ui->leLastIncrement->setText(locale.toString(cpd->lastIncrement,'f', 4));
    this->ui->leDepthIncrement->setText(locale.toString(cpd->depthIncrement,'f', 4));
    this->ui->leTargetDepth->setText(locale.toString(cpd->targetDepth,'f', 4));

    this->ui->leOPName->setText(cpd->profileName);

    this->ui->leSavetyMargin->setText(locale.toString(cpd->savetyMargin,'f', 4));
    this->ui->leZRetract->setText(locale.toString(cpd->zRetract,'f', 4));

    this->ui->leSpindleRPM->setText(locale.toString(cpd->spindleRPM));

    this->ui->leToolDiameter->setText(locale.toString(cpd->toolDiameter,'f', 4));
    this->ui->leToolNumber->setText(locale.toString(cpd->toolNumber));

}

CAMProfileData *CAMProfileSettings::getData() {
    return camProfileData;
}

void CAMProfileSettings::on_bCancel_clicked() {
    this->reject();
}


void CAMProfileSettings::on_bOk_clicked() {
    QLocale locale;
    bool ok;
    camProfileData->feedCutRate=locale.toDouble(ui->leFeedCutRate->text(), &ok);
    camProfileData->feedPlungeRate=locale.toDouble(ui->leFeedPlungeRate->text(), &ok);

    camProfileData->firstIncrement=locale.toDouble(ui->leFirstIncrement->text(), &ok);
    camProfileData->lastIncrement=locale.toDouble(ui->leLastIncrement->text(), &ok);
    camProfileData->depthIncrement=locale.toDouble(ui->leDepthIncrement->text(), &ok);
    camProfileData->targetDepth=locale.toDouble(ui->leTargetDepth->text(), &ok);

    camProfileData->profileName=ui->leOPName->text();

    camProfileData->savetyMargin=locale.toDouble(ui->leSavetyMargin->text(), &ok);
    camProfileData->zRetract=locale.toDouble(ui->leZRetract->text(), &ok);

    camProfileData->spindleRPM=locale.toInt(ui->leSpindleRPM->text(), &ok);

    camProfileData->toolDiameter=locale.toDouble(ui->leToolDiameter->text(), &ok);
    camProfileData->toolNumber=locale.toInt(ui->leToolNumber->text(), &ok);

    this->accept();
}

void CAMProfileSettings::testForm(QString) {
    bool valid=true;
    valid=this->ui->leFeedCutRate->hasAcceptableInput() && valid;
    valid=this->ui->leFeedPlungeRate->hasAcceptableInput() && valid;

    valid=this->ui->leFirstIncrement->hasAcceptableInput() && valid;
    valid=this->ui->leLastIncrement->hasAcceptableInput() && valid;
    valid=this->ui->leDepthIncrement->hasAcceptableInput() && valid;
    valid=this->ui->leTargetDepth->hasAcceptableInput() && valid;

    valid=this->ui->leOPName->hasAcceptableInput() && valid;

    valid=this->ui->leSavetyMargin->hasAcceptableInput() && valid;
    valid=this->ui->leZRetract->hasAcceptableInput() && valid;

    valid=this->ui->leSpindleRPM->hasAcceptableInput() && valid;

    valid=this->ui->leToolDiameter->hasAcceptableInput() && valid;
    valid=this->ui->leToolNumber->hasAcceptableInput() && valid;

    this->ui->bOk->setEnabled(valid);
}
