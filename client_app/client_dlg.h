// client_dlg.h : header file
//

#pragma once

#include "client.h"
#include "register_page.h"
#include "login_page.h"
#include "model_page.h"
#include "file_transfer_page.h"

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
    CModelPage m_ModelPage;
    CFileTransferPage m_FileTransferPage;

	HICON m_hIcon;

    Client &m_Client;

protected:

	// Generated message map functions
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
