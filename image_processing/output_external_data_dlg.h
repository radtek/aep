#pragma once

#include "Resource.h"

// COutputExternalDataDlg dialog

class COutputExternalDataDlg : public CDialog
{
	DECLARE_DYNAMIC(COutputExternalDataDlg)

public:
	COutputExternalDataDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COutputExternalDataDlg();

// Dialog Data
	enum { IDD = IDD_OUTPUT_EXTERNAL_DATA_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    UINT m_OutputId1;
    UINT m_OutputId2;
    UINT m_OutputId3;
    UINT m_OutputId4;
    UINT m_OutputId5;
    UINT m_Width1;
    UINT m_Width2;
    UINT m_Width3;
    UINT m_Width4;
    UINT m_Width5;
    UINT m_Height1;
    UINT m_Height2;
    UINT m_Height3;
    UINT m_Height4;
    UINT m_Height5;
    CString m_FilePath1;
    CString m_FilePath2;
    CString m_FilePath3;
    CString m_FilePath4;
    CString m_FilePath5;
};
