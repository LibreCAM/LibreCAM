/*
 *  rvt_CAMmodificationdata.h
 *  QCad
 *
 *  Created by Ries van Twisk on 7/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CAMPROFILEDATA_H
#define CAMPROFILEDATA_H

#include <QObject>
#include <QString>
#include <QDomDocument>
#include <QDomElement>
#include <QAbstractTableModel>
#include <QList>

class CAMProfileData  {
public:
    CAMProfileData() ;

    enum EnumSpindleDirection {spCW, spCCW, spOff};

    enum EnumCutterCompensation {ccOff, ccLeft, ccRight};

    // Profile
    double savetyMargin;   // Safte marging to move over the surface between operations
    double zRetract;      // Hight between MOB's and start, end of operation
    double targetDepth;     // Target depth of the profile, 0 is top of the surface
    double depthIncrement;  // Increments for each pass if you need to cut in multiple pases, 0 is one pass

    // Cutter Compensation
    double toolDiameter;    // Tool diameter if cutter compensation is enabled
    int toolNumber;         // Tool number for usage in tool tables

    // Feed
    double feedPlungeRate;  // Feedrate during plunge operations (material entry)
    double feedCutRate;     // Feedrate during cutting

    // Spindle
    int spindleRPM; // RPM of the spindle
    EnumSpindleDirection spindleDirection; // Direction of teh spindle

    // optional
    double lastIncrement; // Last step incremental
    double firstIncrement; // First step incremental

    QString profileName;

public:
    QDomElement getDomElement(QDomDocument *doc);

private:

};


class CAMProfileDataModel : public QAbstractTableModel {
    Q_OBJECT

public:
    CAMProfileDataModel(QObject *parent = 0);
    ~CAMProfileDataModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void addProfileData(CAMProfileData *data);
    QList<CAMProfileData *> getList(){return camProfileDataList;}
    void clear(){
        while (!camProfileDataList.isEmpty())
            delete camProfileDataList.takeFirst();
    }

    bool removeRows ( int row, int count, const QModelIndex & parent = QModelIndex());

private:
    QList<CAMProfileData *> camProfileDataList;
};

#endif
