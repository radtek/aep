// add_config_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "add_config_dlg.h"


// CAddConfigDlg dialog

IMPLEMENT_DYNAMIC(CAddConfigDlg, CDialog)

CAddConfigDlg::CAddConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddConfigDlg::IDD, pParent)
    , m_AddFactor1(0)
    , m_AddFactor2(0)
    , m_AddFactor3(0)
    , m_AddFactor4(0)
    , m_AddFactor5(0)
{

}

CAddConfigDlg::~CAddConfigDlg()
{
}

void CAddConfigDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ADD_FACTOR1_TEXT, m_AddFactor1);
    DDX_Text(pDX, IDC_ADD_FACTOR2_TEXT, m_AddFactor2);
    DDX_Text(pDX, IDC_ADD_FACTOR3_TEXT, m_AddFactor3);
    DDX_Text(pDX, IDC_ADD_FACTOR4_TEXT, m_AddFactor4);
    DDX_Text(pDX, IDC_ADD_FACTOR5_TEXT, m_AddFactor5);
}


BEGIN_MESSAGE_MAP(CAddConfigDlg, CDialog)
    ON_BN_CLICKED(IDOK, &CAddConfigDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddConfigDlg message handlers

void CAddConfigDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    OnOK();
}
