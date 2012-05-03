// main_frm.h : interface of the CMainFrame class
//


#pragma once
#include "attribute_bar.h"

class CMainFrame : public CBCGPFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
    CAttributeBar &GetAttributeBar();

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
	CAttributeBar				m_wndOutput;
	CBCGPOutlookBar			m_wndShortcutsBar;
    CBCGPOutlookWnd *m_ShortcutsBarContainer;
	vector<CBCGPOutlookBarPane *> m_PaneList;

	CBCGPToolBarImages	m_UserImages;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	void OnToolsViewUserToolbar (UINT id);
	void OnUpdateToolsViewUserToolbar (CCmdUI* pCmdUI);
	void OnComponentType(UINT id);
    void OnUpdateComponentTypeUI(CCmdUI *cmdUI);
	void OnInternalAlgorithm(UINT id);
    void OnUpdateInternalAlgorithmUI(CCmdUI *cmdUI);
	void OnExternalAlgorithm(UINT id);
    void OnUpdateExternalAlgorithmUI(CCmdUI *cmdUI);
    void OnConnector(UINT id);
    void OnUpdateConnectorUI(CCmdUI *cmdUI);
	afx_msg void OnAppLook(UINT id);
	afx_msg void OnUpdateAppLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()


	BOOL CreateShortcutsBar ();

	UINT	m_nAppLook;
public:
    afx_msg void OnFileExport();
    afx_msg void OnFileDraw();
    afx_msg void OnFileValidate();
};


