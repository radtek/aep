// register_page.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "register_page.h"
#include "utility.h"

// CRegisterPage dialog

IMPLEMENT_DYNAMIC(CRegisterPage, CBCGPPropertyPage)

CRegisterPage::CRegisterPage()
	: CBCGPPropertyPage(CRegisterPage::IDD)
    , m_Name(_T(""))
    , m_Password(_T(""))
    , m_ConfirmPassword(_T(""))
    , m_Client(Client::GetInstance())
{

}

CRegisterPage::~CRegisterPage()
{
}

void CRegisterPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_REGISTER_NAME, m_Name);
    DDX_Text(pDX, IDC_REGISTER_PASSWORD, m_Password);
    DDX_Text(pDX, IDC_REGISTER_CONFIRM_PASSWORD, m_ConfirmPassword);
}


BEGIN_MESSAGE_MAP(CRegisterPage, CPropertyPage)
    ON_BN_CLICKED(IDOK, &CRegisterPage::OnBnClickedOk)
END_MESSAGE_MAP()


// CRegisterPage message handlers

BOOL CRegisterPage::OnInitDialog() 
{
    CBCGPPropertyPage::OnInitDialog();

    return TRUE;
}
void CRegisterPage::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    UpdateData();

    if (m_Name.IsEmpty())
    {
        Utility::PromptErrorMessage(TEXT("用户名不能为空."));
        return;
    }

    if (m_Password.IsEmpty())
    {
        Utility::PromptErrorMessage(TEXT("密码不能为空."));
        return;
    }

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

    if (m_ConfirmPassword != m_Password)
    {
        Utility::PromptErrorMessage(TEXT("两次密码不匹配."));
        return;
    }

    if (!m_Client.IsConnected())
    {
        if (OK != m_Client.Connect())
        {
            Utility::PromptErrorMessage(TEXT("连接服务器失败."));
            return;
        }
    }

    RC rc = m_Client.Register(wstring(m_Name), wstring(m_Password));

    if (RC::USER_BAD_NAME_ERROR == rc)
    {
        Utility::PromptErrorMessage(TEXT("用户名包含非法字符."));
        return;
    }

    if (RC::USER_BAD_PASSWORD_ERROR == rc)
    {
        Utility::PromptErrorMessage(TEXT("密码包含非法字符."));
        return;
    }

    if (RC::USER_EXISTED_ERROR == rc)
    {
        Utility::PromptErrorMessage(TEXT("用户已存在."));
        return;
    }

    if (OK != rc)
    {
        Utility::PromptErrorMessage(TEXT("未知错误."));
        return;
    }

    Utility::PromptMessage(TEXT("注册成功."));
}
