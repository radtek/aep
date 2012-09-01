#pragma once


// CLoopCountDlg dialog

class CLoopCountDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoopCountDlg)

public:
	CLoopCountDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoopCountDlg();

// Dialog Data
	enum { IDD = IDD_LOOP_COUNT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    UINT m_LoopCount;
};
