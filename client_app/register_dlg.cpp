// register_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "register_dlg.h"
#include "client.h"
#include "utility.h"


// CRegisterDlg dialog

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialog)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterDlg::IDD, pParent)
    , m_Name(_T(""))
    , m_Password(_T(""))
    , m_PasswordConfirm(_T(""))
{

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_REGISTER_NAME, m_Name);
    DDX_Text(pDX, IDC_REGISTER_PASSWORD, m_Password);
    DDX_Text(pDX, IDC_REGISTER_PASSWORD_CONFIRM, m_PasswordConfirm);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialog)
    ON_BN_CLICKED(IDOK, &CRegisterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CRegisterDlg message handlers

void CRegisterDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    RC rc;

    UpdateData();

    if (Utility::ContainSpace(m_Name))
    {
        Utility::PromptErrorMessage(TEXT("用户名包含非法字符."));
        return;
    }

    if (Utility::ContainSpace(m_Password))
    {
        Utility::PromptErrorMessage(TEXT("密码包含非法字符."));
        return;
    }

    if (m_Password != m_PasswordConfirm)
    {
        Utility::PromptErrorMessage(TEXT("两次密码不相同."));
        return;
    }

    Client &client = Client::GetInstance();

    if (!client.IsConnected())
    {
        CHECK_RC_MSG_NR(client.Connect());
    }
    if (OK != rc)
    {
        return;
    }

    CHECK_RC_MSG_NR(client.Register(wstring(m_Name), wstring(m_Password)));
    if (OK != rc)
    {
        return;
    }

    OnOK();
}
