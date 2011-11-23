// client_dlg.h : header file
//

#pragma once

#include "register_page.h"
#include "login_page.h"

// CClientDlg dialog
class CClientDlg : public CBCGPPropertySheet
{
	DECLARE_DYNAMIC(CClientDlg)

// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENT_DIALOG };

// Implementation
public:
    virtual ~CClientDlg();

public:
	virtual BOOL OnInitDialog();

public:
    CRegisterPage m_RegisterPage;
    CLoginPage m_LoginPage;

	HICON m_hIcon;

    Client &m_Client;

protected:

	// Generated message map functions
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
