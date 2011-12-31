// server_config_page.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "server_config_page.h"
#include "utility.h"

// CServerConfigPage dialog

IMPLEMENT_DYNAMIC(CServerConfigPage, CBCGPPropertyPage)

CServerConfigPage::CServerConfigPage()
	: CBCGPPropertyPage(CServerConfigPage::IDD)
    , m_Client(Client::GetInstance())
    , m_ServerIp("localhost")
    , m_ServerPort(10086)
{

}

CServerConfigPage::~CServerConfigPage()
{
}

void CServerConfigPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_SERVER_CONFIG_IP, m_ServerIp);
    DDX_Text(pDX, IDC_SERVER_CONFIG_PORT, m_ServerPort);
}


BEGIN_MESSAGE_MAP(CServerConfigPage, CPropertyPage)
    ON_BN_CLICKED(IDOK, &CServerConfigPage::OnBnClickedOk)
END_MESSAGE_MAP()


// CServerConfigPage message handlers

BOOL CServerConfigPage::OnInitDialog() 
{
    CBCGPPropertyPage::OnInitDialog();

    return TRUE;
}

void CServerConfigPage::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    string serverIp = Utility::Wstring2String(wstring(m_ServerIp));
    m_Client.SetHostName(serverIp.c_str());
    m_Client.SetPort(m_ServerPort);
}
