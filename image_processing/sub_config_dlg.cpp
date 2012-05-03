// sub_config_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "sub_config_dlg.h"


// CSubConfigDlg dialog

IMPLEMENT_DYNAMIC(CSubConfigDlg, CDialog)

CSubConfigDlg::CSubConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubConfigDlg::IDD, pParent)
    , m_SubFactor(0)
{

}

CSubConfigDlg::~CSubConfigDlg()
{
}

void CSubConfigDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_SUB_FACTOR_TEXT, m_SubFactor);
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
