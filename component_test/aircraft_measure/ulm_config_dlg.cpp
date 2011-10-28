// ulm_config_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ulm_config_dlg.h"

// CULMConfigDlg dialog

IMPLEMENT_DYNAMIC(CULMConfigDlg, CDialog)

CULMConfigDlg::CULMConfigDlg(UniformLinearMotion *motion, CWnd* pParent /*=NULL*/)
	: CDialog(CULMConfigDlg::IDD, pParent)
    , m_X(0)
    , m_Y(0)
    , m_Z(0)
    , m_Motion(motion)
    , m_Name(_T(""))
{
    m_Name = m_Motion->m_Name;
    m_X = m_Motion->m_Velocity->x;
    m_Y = m_Motion->m_Velocity->y;
    m_Z = m_Motion->m_Velocity->z;
}

CULMConfigDlg::~CULMConfigDlg()
{
}

void CULMConfigDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ULM_X, m_X);
    DDX_Text(pDX, IDC_ULM_Y, m_Y);
    DDX_Text(pDX, IDC_ULM_Z, m_Z);
    DDX_Text(pDX, IDC_ULM_NAME, m_Name);
}


BEGIN_MESSAGE_MAP(CULMConfigDlg, CDialog)
END_MESSAGE_MAP()


// CULMConfigDlg message handlers
