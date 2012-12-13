// file_server_page.cpp : implementation file
//

#include "stdafx.h"
#include "server_app.h"
#include "file_server_page.h"
#include "utility.h"

// CFileServerPage dialog

IMPLEMENT_DYNAMIC(CFileServerPage, CBCGPPropertyPage)

CFileServerPage::CFileServerPage()
	: CBCGPPropertyPage(CFileServerPage::IDD)
    , m_Port(10086)
    , m_RootPath(_T("."))
{

}

CFileServerPage::~CFileServerPage()
{
}

void CFileServerPage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_PORT, m_Port);
    DDX_Text(pDX, IDC_ROOT_PATH, m_RootPath);
}


BEGIN_MESSAGE_MAP(CFileServerPage, CBCGPPropertyPage)
    ON_BN_CLICKED(IDOK, &CFileServerPage::OnBnClickedOk)
END_MESSAGE_MAP()


// CFileServerPage message handlers

BOOL CFileServerPage::OnInitDialog() 
{
    CBCGPPropertyPage::OnInitDialog();

    return TRUE;
}

void CFileServerPage::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    UpdateData();

    m_FileService.Init(m_RootPath, "", m_Port);
    if (OK != m_FileService.Listen())
    {
        Utility::PromptErrorMessage(TEXT("文件服务失败."));
    }
}
