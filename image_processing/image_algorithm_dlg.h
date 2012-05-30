#pragma once

#include "Resource.h"

// CImageAlgorithmDlg dialog

class CImageAlgorithmDlg : public CDialog
{
	DECLARE_DYNAMIC(CImageAlgorithmDlg)

public:
	CImageAlgorithmDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageAlgorithmDlg();

// Dialog Data
	enum { IDD = IDD_IMAGE_ALGORITHM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    UINT m_Width1;
    UINT m_Height1;
    UINT m_Width2;
    UINT m_Height2;
    UINT m_Width3;
    UINT m_Height3;
    UINT m_Width4;
    UINT m_Height4;
    UINT m_Width5;
    UINT m_Height5;
    double m_Factor1;
    double m_Factor2;
    double m_Factor3;
    double m_Factor4;
    double m_Factor5;
    CString m_Name;
    UINT m_FromId;
    CString m_DllFileName;
    CString m_FuncName;
};
