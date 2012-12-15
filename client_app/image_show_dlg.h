#pragma once
#include "afxwin.h"
#include <vector>

using namespace std;

// CImageShowDlg dialog

class CImageShowDlg : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CImageShowDlg)

public:
	CImageShowDlg();
	virtual ~CImageShowDlg();

// Dialog Data
	enum { IDD = IDD_IMAGE_SHOW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    CStatic m_ImageCtrl;

private:
    CString m_Path;
    vector<CString> m_FileNames;
    UINT32 m_CurrentId;
    void ShowImage(const CString &fileName);
    UINT_PTR m_Timer;
    bool m_Started;
    HBITMAP m_Bitmap;
public:
    afx_msg void OnBnClickedSelectPath();
    CString m_FileName;
    afx_msg void OnBnClickedStartPauseButton();
    UINT m_Interval;
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedPrevButton();
    afx_msg void OnBnClickedNextButton();
};
