#pragma once

#include "stdafx.h"
#include "resource.h"
#include "acceleration_linear_motion.h"

// CALMConfigDlg dialog

class CALMConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CALMConfigDlg)

public:
	CALMConfigDlg(AccelerationLinearMotion *motion, CWnd* pParent = NULL);   // standard constructor
	virtual ~CALMConfigDlg();

// Dialog Data
	enum { IDD = IDD_ALM_CONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CString m_Name;
public:
    double m_VelocityX;
public:
    double m_VelocityY;
public:
    double m_VelocityZ;
public:
    double m_AccelerationX;
public:
    double m_AccelerationY;
public:
    double m_AccelerationZ;

public:
    AccelerationLinearMotion *m_Motion;
};
