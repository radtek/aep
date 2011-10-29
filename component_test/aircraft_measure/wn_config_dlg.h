#pragma once

#include "stdafx.h"
#include "resource.h"
#include "white_noise.h"

// CWNConfigDlg dialog

class CWNConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CWNConfigDlg)

public:
	CWNConfigDlg(WhiteNoise *noise, CWnd* pParent = NULL);   // standard constructor
	virtual ~CWNConfigDlg();

// Dialog Data
	enum { IDD = IDD_WN_CONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
    WhiteNoise *m_Noise;
public:
    double m_Factor;
};
