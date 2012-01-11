// control_page.cpp : implementation file
//

#include "stdafx.h"
#include "server_app.h"
#include "control_page.h"
#include "utility.h"

// CControlPage dialog

IMPLEMENT_DYNAMIC(CControlPage, CBCGPPropertyPage)

CControlPage::CControlPage()
	: CBCGPPropertyPage(CControlPage::IDD)
    , m_Server(Server::GetInstance())
    , m_Port(10086)
{

}

CControlPage::~CControlPage()
{
}

void CControlPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_CONTROL_PORT, m_Port);
}


BEGIN_MESSAGE_MAP(CControlPage, CBCGPPropertyPage)
    ON_BN_CLICKED(IDB_CONTROL_START, &CControlPage::OnBnClickedControlStart)
END_MESSAGE_MAP()


// CControlPage message handlers

BOOL CControlPage::OnInitDialog() 
{
    CBCGPPropertyPage::OnInitDialog();

    return TRUE;
}
void CControlPage::OnBnClickedControlStart()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    m_Server.SetPort(m_Port);
    RC rc = m_Server.Listen();
    if (OK != rc)
    {
        Utility::PromptErrorMessage(TEXT("服务器开始服务失败."));
    }
}
