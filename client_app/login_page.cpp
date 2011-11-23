// login_page.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "login_page.h"
#include "utility.h"

// CLoginPage dialog

IMPLEMENT_DYNAMIC(CLoginPage, CBCGPPropertyPage)

CLoginPage::CLoginPage()
	: CBCGPPropertyPage(CLoginPage::IDD)
    , m_Name(_T(""))
    , m_Password(_T(""))
    , m_Client(Client::GetInstance())
{

}

CLoginPage::~CLoginPage()
{
}

void CLoginPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_LOGIN_NAME, m_Name);
    DDX_Text(pDX, IDC_LOGIN_PASSWORD, m_Password);
}


BEGIN_MESSAGE_MAP(CLoginPage, CPropertyPage)
    ON_BN_CLICKED(IDOK, &CLoginPage::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginPage message handlers

BOOL CLoginPage::OnInitDialog() 
{
    CBCGPPropertyPage::OnInitDialog();

    if (OK != m_Client.Init())
    {
        Utility::PromptErrorMessage(TEXT("��ʼ���ͻ���ʧ��."));
        return FALSE;
    }

    return TRUE;
}
void CLoginPage::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    if (m_Client.IsLogined())
    {
        Utility::PromptErrorMessage(TEXT("���Ѿ���½."));
        return;
    }

    UpdateData();

    if (Utility::ContainSpace(m_Name))
    {
        Utility::PromptErrorMessage(TEXT("�û��������Ƿ��ַ�."));
        return;
    }

    if (Utility::ContainSpace(m_Password))
    {
        Utility::PromptErrorMessage(TEXT("��������Ƿ��ַ�."));
        return;
    }

    if (!m_Client.IsConnected())
    {
        if (OK != m_Client.Connect())
        {
            Utility::PromptErrorMessage(TEXT("���ӷ�����ʧ��."));
            return;
        }
    }

    RC rc = m_Client.Login(wstring(m_Name), wstring(m_Password));

    if (RC::USER_BAD_NAME_ERROR == rc)
    {
        Utility::PromptErrorMessage(TEXT("�û��������Ƿ��ַ�."));
        return;
    }

    if (RC::USER_BAD_PASSWORD_ERROR == rc)
    {
        Utility::PromptErrorMessage(TEXT("��������Ƿ��ַ�."));
        return;
    }

    if (RC::USER_UNEXISTS_USER_ERROR == rc)
    {
        Utility::PromptErrorMessage(TEXT("�û�������."));
        return;
    }

    if (RC::USER_WRONG_PASSWORD_ERROR == rc)
    {
        Utility::PromptErrorMessage(TEXT("�������."));
        return;
    }

    Utility::PromptErrorMessage(TEXT("��½�ɹ�."));
}
