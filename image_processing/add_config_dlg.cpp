// add_config_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "add_config_dlg.h"


// CAddConfigDlg dialog

IMPLEMENT_DYNAMIC(CAddConfigDlg, CDialog)

CAddConfigDlg::CAddConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddConfigDlg::IDD, pParent)
    , m_AddFactor(0)
{

}

CAddConfigDlg::~CAddConfigDlg()
{
}

void CAddConfigDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ADD_FACTOR_TEXT, m_AddFactor);
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
