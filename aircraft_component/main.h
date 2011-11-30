// aircraft_component.h : main header file for the aircraft_component DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Caircraft_componentApp
// See aircraft_component.cpp for the implementation of this class
//

class Caircraft_componentApp : public CWinApp
{
public:
	Caircraft_componentApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
