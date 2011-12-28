#pragma once

#include "client.h"
#include "afxwin.h"
#include "afxcmn.h"

// CFileTransferPage dialog

class CFileTransferPage : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CFileTransferPage)

public:
	CFileTransferPage();
	virtual ~CFileTransferPage();

// Dialog Data
	enum { IDD = IDD_FILE_TRANSFER_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_FileList;
private:
    Client &m_Client;
public:
    CProgressCtrl m_FileTransferProgress;
public:
    afx_msg void OnBnClickedUploadButton();
public:
    afx_msg void OnBnClickedDownloadButton();
public:
    afx_msg void OnBnClickedUpdateFileListButton();
protected:
    void GetFileList();
};
