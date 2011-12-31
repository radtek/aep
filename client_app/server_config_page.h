#pragma once

#include "client.h"

// CServerConfigPage dialog

class CServerConfigPage : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CServerConfigPage)

public:
	CServerConfigPage();
	virtual ~CServerConfigPage();

// Dialog Data
	enum { IDD = IDD_SERVER_CONFIG_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
    Client &m_Client;
    CString m_ServerIp;
    int m_ServerPort;
    afx_msg void OnBnClickedOk();
};
