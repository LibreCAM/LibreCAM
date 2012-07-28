/*
 *  rvt_campostprocess.cpp
 *  QCad
 *
 *  Created by Ries van Twisk on 7/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "rvt_campostprocessor.h"



RVT_CamPostprocessor::RVT_CamPostprocessor(const RS_String& postame) 
{
	Py_Initialize();
	PyObject *pName = PyString_FromString(postame.ascii());
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	if (pModule != NULL) {
		p_setOutputFilename = getCallableFunction("setOutputFilename");
	}
}

RVT_CamPostprocessor::~RVT_CamPostprocessor()
{
	if (pModule!=NULL) {
		if (p_setOutputFilename) Py_XDECREF(p_setOutputFilename);
		Py_DECREF(pModule);
		Py_Finalize();
	}
}


/**
 * Return a pointer to a callable Python Function
 */
PyObject *RVT_CamPostprocessor::getCallableFunction(const RS_String& functionName) {
	PyObject* pFunc = PyObject_GetAttrString(pModule, functionName.ascii());
	if (pFunc && PyCallable_Check(pFunc)) {
		return pFunc;
	}
	// TODO add error reporting here
	return NULL;
}


/**
 * Full path to the python object
 */ 
bool RVT_CamPostprocessor::setOutputFilename(const RS_String& postame)
{
	if (pModule==NULL) return false;
	
	PyObject *pArgs = PyTuple_New(1); 
	PyObject *pValue = PyString_FromString(postame.ascii());
	if (!pValue) {
		Py_DECREF(pArgs);
		// Error message here
		return false;
	}
	PyTuple_SetItem(pArgs, 0, pValue);
	PyObject_CallObject(p_setOutputFilename, pArgs);
	Py_DECREF(pArgs);
	Py_DECREF(pValue);
	
	
//	p_setOutputFilename
}

bool RVT_CamPostprocessor::setTolerance(double tolerance)
{
}
