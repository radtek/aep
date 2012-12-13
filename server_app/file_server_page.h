#pragma once

#include "file_service.h"

// CFileServerPage dialog

class CFileServerPage : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CFileServerPage)

public:
	CFileServerPage();   // standard constructor
	virtual ~CFileServerPage();

// Dialog Data
	enum { IDD = IDD_FILE_SERVER_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    int m_Port;
    CString m_RootPath;
    afx_msg void OnBnClickedOk();

private:
    FileService m_FileService;
};
