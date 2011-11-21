#pragma once


// CRegisterDlg dialog

class CRegisterDlg : public CDialog
{
	DECLARE_DYNAMIC(CRegisterDlg)

public:
	CRegisterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRegisterDlg();

// Dialog Data
	enum { IDD = IDD_REGISTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CString m_Name;
public:
    CString m_Password;
public:
    CString m_PasswordConfirm;
public:
    afx_msg void OnBnClickedOk();
};
