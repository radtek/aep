// file_server_app_dlg.h : 头文件
//

#pragma once

#include "file_service.h"

// CFileServerDlg 对话框
class CFileServerDlg : public CDialog
{
// 构造
public:
	CFileServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FILE_SERVER_APP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    int m_Port;
    CString m_RootPath;

    FileService m_FileService;
    afx_msg void OnBnClickedOk();
};
