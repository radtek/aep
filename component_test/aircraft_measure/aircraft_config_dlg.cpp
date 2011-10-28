// aircraft_config_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "aircraft_measure_main.h"
#include "aircraft_config_dlg.h"


// CAircraftConfigDlg dialog

IMPLEMENT_DYNAMIC(CAircraftConfigDlg, CDialog)

CAircraftConfigDlg::CAircraftConfigDlg(Aircraft *aircraft, ComponentList *list, CWnd* pParent /*=NULL*/)
	: CDialog(CAircraftConfigDlg::IDD, pParent)
    , m_Name(_T(""))
    , m_Aircraft(aircraft)
    , m_MotionList(list)
    , m_StartX(0)
    , m_StartY(0)
    , m_StartZ(0)
{
    m_Name = m_Aircraft->m_Name;
    m_StartX = m_Aircraft->m_StartCoordinate->x;
    m_StartY = m_Aircraft->m_StartCoordinate->y;
    m_StartZ = m_Aircraft->m_StartCoordinate->z;
}

CAircraftConfigDlg::~CAircraftConfigDlg()
{
}

void CAircraftConfigDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_AIRCRAFT_NAME, m_Name);
    DDX_Control(pDX, IDC_AIRCRAFT_MOTION, m_Motion);
    DDX_Text(pDX, IDC_AIRCRAFT_START_X, m_StartX);
    DDX_Text(pDX, IDC_AIRCRAFT_START_Y, m_StartY);
    DDX_Text(pDX, IDC_AIRCRAFT_START_Z, m_StartZ);
}


BEGIN_MESSAGE_MAP(CAircraftConfigDlg, CDialog)
    ON_CBN_SELCHANGE(IDC_AIRCRAFT_MOTION, &CAircraftConfigDlg::OnCbnSelchangeAircraftMotion)
END_MESSAGE_MAP()


// CAircraftConfigDlg message handlers

BOOL CAircraftConfigDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    for (UINT32 i = 0; i < m_MotionList->size(); ++i)
    {
        IComponent *component;
        RC rc = (*m_MotionList)[i]->GetInterface(CLIENT_CIID_MOTION, (void **)&component);
        if (OK == rc && component)
        {
            LPWSTR buf;
            component->GetName(&buf);
            CString cs(buf);
            m_Motion.AddString(cs);
            int item = m_Motion.GetCount() - 1;
            m_Motion.SetItemData(item, (DWORD_PTR)component);

            IComponent *motion = m_Aircraft->m_Motion;
            if (motion)
            {
                motion->GetName(&buf);
                if (cs == CString(buf))
                {
                    m_Motion.SetCurSel(item);
                }
            }
        }
    }
    return TRUE;
}

void CAircraftConfigDlg::OnCbnSelchangeAircraftMotion()
{
    // TODO: Add your control notification handler code here
    int sel = m_Motion.GetCurSel();
    m_Aircraft->m_Motion = (IMotion *)m_Motion.GetItemData(sel);
}
