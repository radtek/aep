// main_frm.h : interface of the CMainFrame class
//


#pragma once
#include "output_bar.h"

class CMainFrame : public CBCGPFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPStatusBar			m_wndStatusBar;
	CBCGPMenuBar			m_wndMenuBar;
	CBCGPToolBar			m_wndToolBar;
	COutputBar				m_wndOutput;
	CBCGPOutlookBar			m_wndShortcutsBar;
	vector<CBCGPOutlookBarPane *> m_InterfacePaneList;

	CBCGPToolBarImages	m_UserImages;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	void OnToolsViewUserToolbar (UINT id);
	void OnUpdateToolsViewUserToolbar (CCmdUI* pCmdUI);
	void OnOutlookBarShortcut(UINT id);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()


	BOOL CreateShortcutsBar ();

	UINT	m_nAppLook;
};


