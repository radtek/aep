#pragma once

#include "server.h"

// CControlPage dialog

class CControlPage : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CControlPage)

public:
	CControlPage();
	virtual ~CControlPage();

// Dialog Data
	enum { IDD = IDD_CONTROL_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
    Server &m_Server;
    afx_msg void OnBnClickedControlStart();
    int m_Port;
};
