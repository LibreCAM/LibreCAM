/*****************************************************************************/
/*  camprofiledata.cpp - plugin example for LibreCAD                         */
/*                                                                           */
/*  Copyright (C) 2011 R. van Twisk ries@vantwisk.n                          */
/*                                                                           */
/*  This library is free software, licensed under the terms of the GNU       */
/*  General Public License as published by the Free Software Foundation,     */
/*  either version 2 of the License, or (at your option) any later version.  */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.    */
/*****************************************************************************/

#include "camprofiledata.h"
#include <QString>
#include <QDomDocument>
#include <QDomElement>
#include <QVariant>

CAMProfileData::CAMProfileData() {
    // Profile
    savetyMargin=6;
    zRetract=100;
    targetDepth=1;
    depthIncrement=0.5;

    // Cutter Compensation
    toolDiameter=6;
    toolNumber=-1;

    // Feed
    feedPlungeRate=2000;
    feedCutRate=6000;

    // Spindle
    spindleRPM=10000;
    spindleDirection=CAMProfileData::spCCW;

    // optional
    lastIncrement=0; // Last step incremental
    firstIncrement=0; // First step incremental

    profileName="New";
}


#define ADDATTRIBUTE(name, value) \
element=doc->createElement(name); \
        element.appendChild(doc->createTextNode(value.toString())); \
        tag.appendChild(element);

QDomElement CAMProfileData::getDomElement(QDomDocument *doc) {
    QDomElement tag = doc->createElement("CAMProfileData");
    QDomElement element;

    ADDATTRIBUTE("savetyMargin", QVariant(savetyMargin));
    ADDATTRIBUTE("zRetract", QVariant(zRetract));
    ADDATTRIBUTE("targetDepth", QVariant(targetDepth));
    ADDATTRIBUTE("depthIncrement", QVariant(depthIncrement));

    ADDATTRIBUTE("toolDiameter", QVariant(toolDiameter));
    ADDATTRIBUTE("toolNumber", QVariant(toolNumber));

    ADDATTRIBUTE("feedPlungeRate", QVariant(feedPlungeRate));
    ADDATTRIBUTE("feedCutRate", QVariant(feedCutRate));

    ADDATTRIBUTE("spindleRPM", QVariant(spindleRPM));
    ADDATTRIBUTE("spindleDirection", QVariant(spindleDirection));

    ADDATTRIBUTE("lastIncrement", QVariant(lastIncrement));
    ADDATTRIBUTE("firstIncrement", QVariant(firstIncrement));

    ADDATTRIBUTE("profileName", QVariant(profileName));

    return tag;
}



CAMProfileDataModel::CAMProfileDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}


CAMProfileDataModel::~CAMProfileDataModel()
{
    while (!camProfileDataList.isEmpty())
         delete camProfileDataList.takeFirst();
}

void CAMProfileDataModel::addProfileData(CAMProfileData *data)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    camProfileDataList.append(data);
    endInsertRows();
}

int CAMProfileDataModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return camProfileDataList.size();
}

int CAMProfileDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

QVariant CAMProfileDataModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() > camProfileDataList.count())
        return QVariant();

    if (!index.isValid())
        return QVariant();

    if (index.row() >= camProfileDataList.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        CAMProfileData *cpd = camProfileDataList.at(index.row());

        switch (index.column()) {
        case 0:
            return cpd->profileName;
        case 1:
            return cpd->toolDiameter;
        case 2:
            return cpd->toolNumber;
        case 3:
            return cpd->feedCutRate;
        }
    }
    return QVariant();
}

QVariant CAMProfileDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Name");
        case 1:
            return tr("Tool");
        case 2:
            return tr("Tool No:");
        case 3:
            return tr("FeedRate");

        default:
            return QVariant();
        }
    }
    return QVariant();
}


bool CAMProfileDataModel::removeRows ( int row, int count, const QModelIndex & parent) {
    int lastRow = row + count - 1;
    beginRemoveRows(parent, row, lastRow);
    for (int i = lastRow; i >= row; --i) {
        camProfileDataList.removeAt(i);
    }
    endRemoveRows();
    return true;
}

