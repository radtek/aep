#pragma once

#include "resource.h"

// CSubConfigDlg dialog

class CSubConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubConfigDlg)

public:
	CSubConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubConfigDlg();

// Dialog Data
	enum { IDD = IDD_SUB_CONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    double m_SubFactor;
    afx_msg void OnBnClickedOk();
};
