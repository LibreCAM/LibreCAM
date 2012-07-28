
#include "rvt_actioncammakeprofile.h"
#include "rs_selection.h"
#include "rvt_campostprocessor.h"

RVT_ActionCamMakeProfile::RVT_ActionCamMakeProfile(RS_EntityContainer& container,
                                       RS_GraphicView& graphicView)
        :RS_ActionInterface("Add Profile", container, graphicView) {}


QAction* RVT_ActionCamMakeProfile::createGUIAction(RS2::ActionType /*type*/, QObject* /*parent*/) {
    QAction* action = new QAction(tr("Add Profile"), tr("&Add Profile"),
                                  QKeySequence(), NULL);
    action->setStatusTip(tr("Add Profile"));

    return action;
}

void RVT_ActionCamMakeProfile::trigger() {
    RS_DEBUG->print("RVT_ActionCamMakeProfile::trigger add profile");
    if (RS_DIALOGFACTORY != NULL) {
        if (RS_DIALOGFACTORY->requestCamProfileDialog(data)) {
			
			RS_Layer* camLayer=makeNewLayer(data.profileName);
			graphic->addLayer(camLayer);
//			graphic->activateLayer(camLayer);

			RS_Pen layerpen=RS_Pen(RS_Color(210,105,30), RS2::Width11, RS2::SolidLine);
			camLayer->setPen(layerpen);
			
			RS_Selection s(*container, graphicView);
			
			// Copy selected items into buffer
			RS_PtrList<RS_Entity> entities;
			for (RS_Entity* en = container->firstEntity(); en != NULL; en = container->nextEntity()) {
				if (en!=NULL && en->isSelected())
					entities.append(en);
			}
			
			// Copy selected items in the buffer 
			for (RS_Entity* en = entities.first(); en != NULL; en = entities.next()) {
				if (en->getCamId().length()>0) { // Entity implements getCamId so we can work with it
					RS_String camid=en->getCamId();
					RS_Entity *cloned=en->clone();
					cloned->setLayer(camLayer);
					cloned->setSelected(false);
					container->addEntity(cloned);
				}
			}
			profileLayer(camLayer, "default", "/tmp/out");
			RS_DIALOGFACTORY->updateSelectionWidget(container->countSelected());
		}
	}
    finish();
}

void RVT_ActionCamMakeProfile::profileLayer(RS_Layer *layer, const RS_String& postprocessorname, const RS_String& outputFN) 
{
	RVT_CamPostprocessor *postprocessor= new RVT_CamPostprocessor(postprocessorname);
	postprocessor->setOutputFilename(outputFN);
	/*
	RVT_CamProfile *profile= new RVT_CamProfile(postprocessor);
	
	if (postprocessor->isValid()) {
		postprocessor->run();
	} */
	
}


/**
 * Create a new layer with the given name, or create a new profile name
 */
RS_Layer* RVT_ActionCamMakeProfile::makeNewLayer(const QString &newName) {
	// Set to 3, because I had sometimes crashes when set >0
	QString layer_name = "";
	if (newName.length()==0) {
		layer_name = "__profile";
	} else {
		layer_name=newName;
	}
	
	
	RS_LayerList* layerList = graphic->getLayerList();
	
	int i = 2;
	
	if (layerList!=NULL) {
		while (layerList->find(layer_name) > 0)
			layer_name.sprintf(layer_name+"_%d", i++);
	}
	
	return new RS_Layer(layer_name);
}

void RVT_ActionCamMakeProfile::init(int status) {
    RS_ActionInterface::init(status);
    trigger();
}

// EOF

