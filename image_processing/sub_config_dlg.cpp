// sub_config_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "sub_config_dlg.h"


// CSubConfigDlg dialog

IMPLEMENT_DYNAMIC(CSubConfigDlg, CDialog)

CSubConfigDlg::CSubConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubConfigDlg::IDD, pParent)
    , m_SubFactor1(0)
    , m_SubFactor2(0)
    , m_SubFactor3(0)
    , m_SubFactor4(0)
    , m_SubFactor5(0)
{

}

CSubConfigDlg::~CSubConfigDlg()
{
}

void CSubConfigDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_SUB_FACTOR1_TEXT, m_SubFactor1);
    DDX_Text(pDX, IDC_SUB_FACTOR2_TEXT, m_SubFactor2);
    DDX_Text(pDX, IDC_SUB_FACTOR3_TEXT, m_SubFactor3);
    DDX_Text(pDX, IDC_SUB_FACTOR4_TEXT, m_SubFactor4);
    DDX_Text(pDX, IDC_SUB_FACTOR5_TEXT, m_SubFactor5);
}


BEGIN_MESSAGE_MAP(CSubConfigDlg, CDialog)
    ON_BN_CLICKED(IDOK, &CSubConfigDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSubConfigDlg message handlers

void CSubConfigDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    OnOK();
}
