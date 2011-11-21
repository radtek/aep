// login_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "login_dlg.h"
#include "client.h"
#include "utility.h"


// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
    , m_Name(_T(""))
    , m_Password(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_LOGIN_NAME, m_Name);
    DDX_Text(pDX, IDC_LOGIN_PASSWORD, m_Password);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
    ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDlg message handlers

void CLoginDlg::OnBnClickedOk()
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

    Client &client = Client::GetInstance();

    if (!client.IsConnected())
    {
        CHECK_RC_MSG_NR(client.Connect());
    }
    if (OK != rc)
    {
        return;
    }

    CHECK_RC_MSG_NR(client.Login(wstring(m_Name), wstring(m_Password)));
    if (OK != rc)
    {
        return;
    }

    OnOK();
}

void CLoginDlg::OnBnClickedCancel()
{
    // TODO: Add your control notification handler code here
    RC rc;

    Client &client = Client::GetInstance();

    CHECK_RC_MSG_NR(client.Disconnect());

    OnCancel();
}
