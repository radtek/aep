// file_insertDlg.h : 头文件
//

#pragma once


// Cfile_insertDlg 对话框
class Cfile_insertDlg : public CDialog
{
// 构造
public:
	Cfile_insertDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FILE_INSERT_DIALOG };

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
    CString m_Dir;
    CString m_Prefix;
    CString m_Suffix;
    UINT m_Start;
    UINT m_End;
    afx_msg void OnBnClickedOk();
};
