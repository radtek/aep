#pragma once

#include "resource.h"

// CAddConfigDlg dialog

class CAddConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddConfigDlg)

public:
	CAddConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddConfigDlg();

// Dialog Data
	enum { IDD = IDD_ADD_CONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    double m_AddFactor;
    afx_msg void OnBnClickedOk();
};
