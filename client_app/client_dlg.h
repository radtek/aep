// client_dlg.h : header file
//

#pragma once

#include "client.h"
#include "evaluate.h"
#include "server_config_page.h"
#include "register_page.h"
#include "login_page.h"
#include "model_page.h"
#include "file_transfer_page.h"
#include "file_service_page.h"
#include "evaluate_page.h"
#include "image_show_dlg.h"

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
    CServerConfigPage m_ServerConfigPage;
    CRegisterPage m_RegisterPage;
    CLoginPage m_LoginPage;
    CModelPage m_ModelPage;
    CFileTransferPage m_FileTransferPage;
    CFileServicePage m_FileServicePage;
    CEvaluatePage m_EvaluatePage;
    CImageShowDlg m_ImageShowPage;

	HICON m_hIcon;

    Client &m_Client;
    Evaluate &m_Evaluate;

protected:

	// Generated message map functions
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
