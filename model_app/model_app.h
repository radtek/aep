// model_app.h : main header file for the model_app application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "platform.h"
#include <engine.h>

// CModelApp:
// See model_app.cpp for the implementation of this class
//

class CModelApp : public CWinApp,
							public CBCGPWorkspace
{
public:
	CModelApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
    Platform &m_Platform;
    Engine *m_Engine;
};

extern CModelApp theApp;