// client_dlg.h : ͷ�ļ�
//

#pragma once

#include "client.h"

// CClientDlg �Ի���
class CClientDlg : public CDialog
{
// ����
public:
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

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
    Client m_Client;
public:
    afx_msg void OnBnClickedLogin1();
public:
    afx_msg void OnBnClickedConnect();
public:
    afx_msg void OnBnClickedLogin2();
public:
    afx_msg void OnBnClickedLogin3();
};
