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
    RC InitComponentInfoList();
    CImageList m_ComponentInfoImageList;
    CListCtrl m_ComponentInfoList;
    ComponentInfoList m_CComponentInfoList;

    void *m_DllHandle;
    afx_msg void OnNMRclickComponentInfoList(NMHDR *pNMHDR, LRESULT *pResult);
    RC InsertComponent(UINT32 componentId);

    CImageList m_ComponentImageList;
    CListCtrl m_ComponentList;
    ComponentList m_CComponentList;
    afx_msg void OnNMRclickComponentList(NMHDR *pNMHDR, LRESULT *pResult);
    RC DeleteComponent(UINT32 componentId);
};
