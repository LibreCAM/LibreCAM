/*****************************************************************************/
/*  librecam.cpp - plugin example for LibreCAD                               */
/*                                                                           */
/*  Copyright (C) 2011 R. van Twisk ries@vantwisk.n                          */
/*                                                                           */
/*  This library is free software, licensed under the terms of the GNU       */
/*  General Public License as published by the Free Software Foundation,     */
/*  either version 2 of the License, or (at your option) any later version.  */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.    */
/*****************************************************************************/

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QList>
#include <QSettings>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDockWidget>;
#include <QMainWindow>;

#include "document_interface.h"
#include "librecam.h"
#include "profile/src/camprofiledata.h"
#include "profile/ui/camprofilewidget.h"
#include "profile/ui/camprofilesettingslist.h"

librecam::librecam() {
    camProfileWidget=0;
}
librecam::~librecam() {
    if (camProfileWidget==0) delete camProfileWidget;
}

QString librecam::name() const
 {
     return (tr("rvt - Profile"));
 }

PluginCapabilities librecam::getCapabilities() const
{
    PluginCapabilities pluginCapabilities;
    pluginCapabilities.menuEntryPoints
            << PluginMenuLocation("RVT-CAM/Profile", "Profile Preference")
            << PluginMenuLocation("RVT-CAM", "Profile Tools")
            << PluginMenuLocation("RVT-CAM", "Machine Setup");
    return pluginCapabilities;
}



void librecam::execComm(Document_Interface *doc,
                             QWidget *mainWindow, QString cmd)
{
    Q_UNUSED(doc);

    if (cmd=="Profile Tools") {
        showProfileTools(doc, (QMainWindow*)mainWindow);
    } else if (cmd=="Profile Preference") {
        CAMProfileSettingsList cps(mainWindow);
        int result =  cps.exec();
        //    if (result == QDialog::Accepted)
        //        pdt.procesAction(doc);
    } else if (cmd=="Machine Setup") {
    }

}

/**
  * Show profiling document widget on the screen
  *
  */
void librecam::showProfileTools(Document_Interface *doc, QMainWindow *mainWindow) {
    Q_UNUSED(doc);
    QDockWidget *dw = new QDockWidget("Profile Tools", mainWindow);
    camProfileWidget = new CAMProfileWidget(dw);
    camProfileWidget->setFocusPolicy(Qt::NoFocus);
    dw->setWidget(camProfileWidget);
    mainWindow->addDockWidget(Qt::RightDockWidgetArea , dw);
}

Q_EXPORT_PLUGIN2(librecam, librecam);
