// file_server_app_dlg.h : ͷ�ļ�
//

#pragma once

#include "file_service.h"

// CFileServerDlg �Ի���
class CFileServerDlg : public CDialog
{
// ����
public:
	CFileServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FILE_SERVER_APP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
