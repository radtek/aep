#pragma once
#include "aircraft_measure_ifaces.h"
#include "stdafx.h"
#include "resource.h"
#include "afxwin.h"

// CAircraftConfigDlg dialog

class CAircraftConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CAircraftConfigDlg)

public:
	CAircraftConfigDlg(ComponentList *list, CWnd* pParent = NULL);   // standard constructor
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
    ComponentList *m_MotionList;
    CComboBox m_Motion;
};
