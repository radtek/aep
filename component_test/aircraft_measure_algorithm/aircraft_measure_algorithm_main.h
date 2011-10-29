// aircraft_measure_algorithm.h : main header file for the aircraft_measure_algorithm DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Caircraft_measure_algorithmApp
// See aircraft_measure_algorithm.cpp for the implementation of this class
//

class Caircraft_measure_algorithmApp : public CWinApp
{
public:
	Caircraft_measure_algorithmApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
