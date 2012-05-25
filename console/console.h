// console.h : main header file for the console DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CConsoleApp
// See console.cpp for the implementation of this class
//

class CConsoleApp : public CWinApp
{
public:
	CConsoleApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
