#pragma once

#include "stdafx.h"
#include "resource.h"

#include "aircraft.h"

// CModelRunDlg dialog

class CModelRunDlg : public CDialog
{
	DECLARE_DYNAMIC(CModelRunDlg)

public:
	CModelRunDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModelRunDlg();

// Dialog Data
	enum { IDD = IDD_MODEL_RUN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    double m_MeCoordX;
public:
    double m_MeCoordY;
public:
    double m_MeCoordZ;
public:
    double m_EnemyCoordX;
public:
    double m_EnemyCoordY;
public:
    double m_EnemyCoordZ;
public:
    double m_MeVX;
public:
    double m_MeVY;
public:
    double m_MeVZ;
public:
    double m_EnemyVX;
public:
    double m_EnemyVY;
public:
    double m_EnemyVZ;
public:
    double m_T;
public:
    afx_msg void OnBnClickedModelRun();

public:
    Aircraft *m_Me;
    Aircraft *m_Enemy;
};
