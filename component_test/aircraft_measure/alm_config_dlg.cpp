// alm_config_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "alm_config_dlg.h"

// CALMConfigDlg dialog

IMPLEMENT_DYNAMIC(CALMConfigDlg, CDialog)

CALMConfigDlg::CALMConfigDlg(AccelerationLinearMotion *motion, CWnd* pParent /*=NULL*/)
	: CDialog(CALMConfigDlg::IDD, pParent)
    , m_Name(_T(""))
    , m_VelocityX(0)
    , m_VelocityY(0)
    , m_VelocityZ(0)
    , m_AccelerationX(0)
    , m_AccelerationY(0)
    , m_AccelerationZ(0)
    , m_Motion(motion)
{
    m_Name = m_Motion->m_Name;
    m_VelocityX = m_Motion->m_Velocity->x;
    m_VelocityY = m_Motion->m_Velocity->y;
    m_VelocityZ = m_Motion->m_Velocity->z;
    m_AccelerationX = m_Motion->m_Acceleration->x;
    m_AccelerationY = m_Motion->m_Acceleration->y;
    m_AccelerationZ = m_Motion->m_Acceleration->z;
}

CALMConfigDlg::~CALMConfigDlg()
{
}

void CALMConfigDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ALM_NAME, m_Name);
    DDX_Text(pDX, IDC_ALM_V_X, m_VelocityX);
    DDX_Text(pDX, IDC_ALM_V_Y, m_VelocityY);
    DDX_Text(pDX, IDC_ALM_V_Z, m_VelocityZ);
    DDX_Text(pDX, IDC_ALM_A_X, m_AccelerationX);
    DDX_Text(pDX, IDC_ALM_A_Y, m_AccelerationY);
    DDX_Text(pDX, IDC_ALM_A_Z, m_AccelerationZ);
}


BEGIN_MESSAGE_MAP(CALMConfigDlg, CDialog)
END_MESSAGE_MAP()


// CALMConfigDlg message handlers
