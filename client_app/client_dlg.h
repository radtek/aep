// client_dlg.h : ͷ�ļ�
//

#pragma once

#include "client.h"
#include "afxwin.h"

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
    Client &m_Client;
public:
    CButton m_LoginButton;
public:
    afx_msg void OnBnClickedLogin();
public:
    CButton m_RegisterButton;
public:
    afx_msg void OnBnClickedRegister();
};
