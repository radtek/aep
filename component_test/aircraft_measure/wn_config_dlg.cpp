// wn_config_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "wn_config_dlg.h"


// CWNConfigDlg dialog

IMPLEMENT_DYNAMIC(CWNConfigDlg, CDialog)

CWNConfigDlg::CWNConfigDlg(WhiteNoise *noise, CWnd* pParent /*=NULL*/)
	: CDialog(CWNConfigDlg::IDD, pParent)
    , m_Noise(noise)
    , m_Factor(0)
{
    m_Factor = m_Noise->m_Factor;
}

CWNConfigDlg::~CWNConfigDlg()
{
}

void CWNConfigDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_WN_FACTOR, m_Factor);
}


BEGIN_MESSAGE_MAP(CWNConfigDlg, CDialog)
END_MESSAGE_MAP()


// CWNConfigDlg message handlers
