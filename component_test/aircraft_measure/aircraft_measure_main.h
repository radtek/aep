// aircraft_measure.h : main header file for the aircraft_measure DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Caircraft_measureApp
// See aircraft_measure.cpp for the implementation of this class
//

class Caircraft_measureApp : public CWinApp
{
public:
	Caircraft_measureApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
