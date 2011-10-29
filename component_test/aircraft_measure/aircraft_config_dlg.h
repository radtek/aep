#pragma once

#include "stdafx.h"
#include "resource.h"
#include "aircraft.h"

// CAircraftConfigDlg dialog

class CAircraftConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CAircraftConfigDlg)

public:
	CAircraftConfigDlg(Aircraft *aircraft, CWnd* pParent = NULL);   // standard constructor
	virtual ~CAircraftConfigDlg();

// Dialog Data
	enum { IDD = IDD_AIRCRAFT_CONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    BOOL OnInitDialog();
public:
    CString m_Name;
public:
    CComboBox m_Motion;
public:
    Aircraft *m_Aircraft;
public:
    double m_StartX;
public:
    double m_StartY;
public:
    double m_StartZ;
public:
    afx_msg void OnCbnSelchangeAircraftMotion();
};
