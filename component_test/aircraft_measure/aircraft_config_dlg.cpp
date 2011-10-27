// aircraft_config_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "aircraft_measure_main.h"
#include "aircraft_config_dlg.h"


// CAircraftConfigDlg dialog

IMPLEMENT_DYNAMIC(CAircraftConfigDlg, CDialog)

CAircraftConfigDlg::CAircraftConfigDlg(ComponentList *list, CWnd* pParent /*=NULL*/)
	: CDialog(CAircraftConfigDlg::IDD, pParent)
    , m_Name(_T(""))
    , m_MotionList(list)
{

}

CAircraftConfigDlg::~CAircraftConfigDlg()
{
}

void CAircraftConfigDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_AIRCRAFT_NAME, m_Name);
    DDX_Control(pDX, IDC_AIRCRAFT_MOTION, m_Motion);
}


BEGIN_MESSAGE_MAP(CAircraftConfigDlg, CDialog)
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
        }
    }
    return TRUE;
}
