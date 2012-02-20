#pragma once

#include "client.h"

// CLoginPage dialog

class CLoginPage : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CLoginPage)

public:
	CLoginPage();
	virtual ~CLoginPage();

// Dialog Data
	enum { IDD = IDD_LOGIN_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    CString m_Name;
public:
    CString m_Password;

private:
    Client &m_Client;
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedLogout();
};
