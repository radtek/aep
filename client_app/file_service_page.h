#pragma once

#include "evaluate.h"

// CFileServicePage dialog

class CFileServicePage : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CFileServicePage)

public:
	CFileServicePage();   // standard constructor
	virtual ~CFileServicePage();

// Dialog Data
	enum { IDD = IDD_FILE_SERIVCE_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
    CString m_FileServerHostName;
    int m_FileServerPort;
    CString m_ModelHostName;
    int m_ModelPort;

private:
    Evaluate &m_Evaluate;
public:
    afx_msg void OnBnClickedOk();
    CString m_RootPath;
};
