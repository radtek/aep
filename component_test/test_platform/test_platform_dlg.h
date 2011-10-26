// test_platform_dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "component.h"


// CTestPlatformDlg �Ի���
class CTestPlatformDlg : public CDialog
{
// ����
public:
	CTestPlatformDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_PLATFORM_DIALOG };

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
private:
    RC InitComponent();
    CImageList m_ImageList;
    CListCtrl m_ComponentList;
    ComponentInfoList m_ComponentInfoList;

    void *m_DllHandle;
};
