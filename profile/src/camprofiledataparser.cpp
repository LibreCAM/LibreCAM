#include "camprofiledataparser.h"
#include "camprofiledata.h"
#include <Qlist>
#include <QString>

/**
  * Class to parse the profile data within the XML file.
  * Use QSaxParser for this class
  *
  */
CAMProfileDataParser::CAMProfileDataParser(CAMProfileDataModel *camProfileDataModel)
{
    this->camProfileDataModel=camProfileDataModel;
}

bool CAMProfileDataParser::startDocument()
{
    inProfileData = false;
    return true;
}
bool CAMProfileDataParser::endElement( const QString& , const QString& , const QString &name )
{
    if( name == "CAMProfileData" ) {
        camProfileDataModel->addProfileData(newSet);
        inProfileData = false;
    }

    if (inProfileData) {
        if( name == "savetyMargin" ) newSet->savetyMargin=currentText.toDouble();
        if( name == "zRetract" ) newSet->zRetract=currentText.toDouble();
        if( name == "targetDepth" ) newSet->targetDepth=currentText.toDouble();
        if( name == "depthIncrement" ) newSet->depthIncrement=currentText.toDouble();
        if( name == "toolDiameter" ) newSet->toolDiameter=currentText.toDouble();
        if( name == "toolNumber" ) newSet->toolNumber=currentText.toInt();
        /*
        if( name == "toolCutterCompensation" ) {
            QString compensation=currentText;
            if (compensation=="ccOff") {
                newSet->toolCutterCompensation=CAMProfileData::ccOff;
            } else if (compensation=="ccLeft") {
                newSet->toolCutterCompensation=CAMProfileData::ccLeft;
            } else if (compensation=="ccRight") {
                newSet->toolCutterCompensation=CAMProfileData::ccRight;
            }
        }*/
        if( name == "feedPlungeRate" ) newSet->feedPlungeRate=currentText.toDouble();
        if( name == "feedCutRate" ) newSet->feedCutRate=currentText.toDouble();
        if( name == "spindleRPM" ) newSet->spindleRPM=currentText.toInt();
        if( name == "spindleDirection" ) {
            QString direction=currentText;
            if (direction=="spCW") {
                newSet->spindleDirection=CAMProfileData::spCW;
            } else if (direction=="spCCW") {
                newSet->spindleDirection=CAMProfileData::spCCW;
            } else if (direction=="spOff") {
                newSet->spindleDirection=CAMProfileData::spOff;
            }
        }
        if( name == "lastIncrement" ) newSet->lastIncrement=currentText.toDouble();
        if( name == "firstIncrement" ) newSet->firstIncrement=currentText.toDouble();
        if( name == "profileName" ) newSet->profileName=currentText;
    }

    return true;
}

bool CAMProfileDataParser::characters(const QString &str)
{
    currentText += str;
    return true;
}

bool CAMProfileDataParser::startElement( const QString&, const QString&, const QString &name, const QXmlAttributes & )
{
    if (name=="CAMProfileData") {
        newSet=new CAMProfileData();
        inProfileData = true;
    }
    currentText="";

    return true;
}
