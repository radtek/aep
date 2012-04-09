// main.h : main header file for the aircraft_component_target DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Caircraft_component_targetApp
// See main.cpp for the implementation of this class
//

class CImageProcessingApp : public CWinApp
{
public:
	CImageProcessingApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
