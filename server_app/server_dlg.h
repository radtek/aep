// server_dlg.h : header file
//

#pragma once

#include "server.h"
#include "control_page.h"
#include "log_page.h"
#include "file_server_page.h"

// CServerDlg dialog
class CServerDlg : public CBCGPPropertySheet
{
	DECLARE_DYNAMIC(CServerDlg)

// Construction
public:
	CServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SERVER_DIALOG };

// Implementation
public:
    virtual ~CServerDlg();

public:
	virtual BOOL OnInitDialog();

public:
    CControlPage m_ControlPage;
    CLogPage m_LogPage;
    CFileServerPage m_FileServerPage;

	HICON m_hIcon;

    Server &m_Server;

protected:

	// Generated message map functions
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
