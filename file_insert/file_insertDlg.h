// file_insertDlg.h : ͷ�ļ�
//

#pragma once


// Cfile_insertDlg �Ի���
class Cfile_insertDlg : public CDialog
{
// ����
public:
	Cfile_insertDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FILE_INSERT_DIALOG };

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
    CString m_Dir;
    CString m_Prefix;
    CString m_Suffix;
    UINT m_Start;
    UINT m_End;
    afx_msg void OnBnClickedOk();
};
