#pragma once

#include "stdafx.h"
#include "resource.h"
#include "uniform_linear_motion.h"

// CULMConfigDlg dialog

class CULMConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CULMConfigDlg)

public:
	CULMConfigDlg(UniformLinearMotion *motion, CWnd* pParent = NULL);   // standard constructor
	virtual ~CULMConfigDlg();

// Dialog Data
	enum { IDD = IDD_ULM_CONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    double m_X;
public:
    double m_Y;
public:
    double m_Z;

public:
    UniformLinearMotion *m_Motion;
public:
    CString m_Name;
};
