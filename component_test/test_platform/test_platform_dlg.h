// test_platform_dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "component.h"


// CTestPlatformDlg 对话框
class CTestPlatformDlg : public CDialog
{
// 构造
public:
	CTestPlatformDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_PLATFORM_DIALOG };

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
private:
    RC InitComponent();
    CImageList m_ImageList;
    CListCtrl m_ComponentList;
    ComponentInfoList m_ComponentInfoList;

    void *m_DllHandle;
};
