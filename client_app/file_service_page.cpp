// file_service_page.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "file_service_page.h"
#include "utility.h"

// CFileServicePage dialog

IMPLEMENT_DYNAMIC(CFileServicePage, CBCGPPropertyPage)

CFileServicePage::CFileServicePage()
	: CBCGPPropertyPage(CFileServicePage::IDD)
    , m_FileServerHostName(_T("localhost"))
    , m_FileServerPort(10086)
    , m_ModelHostName(_T("localhost"))
    , m_ModelPort(10087)
    , m_Evaluate(Evaluate::GetInstance())
    , m_RootPath(_T("."))
{

}

CFileServicePage::~CFileServicePage()
{
}

void CFileServicePage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_FILE_SERVICE_FILE_SERVER_IP, m_FileServerHostName);
    DDX_Text(pDX, IDC_FILE_SERVICE_FILE_SERVER_PORT, m_FileServerPort);
    DDX_Text(pDX, IDC_FILE_SERVICE_MODEL_IP, m_ModelHostName);
    DDX_Text(pDX, IDC_FILE_SERVICE_MODEL_PORT, m_ModelPort);
    DDX_Text(pDX, IDC_FILE_SERVICE_ROOT_PATH, m_RootPath);
}


BEGIN_MESSAGE_MAP(CFileServicePage, CPropertyPage)
    ON_BN_CLICKED(IDOK, &CFileServicePage::OnBnClickedOk)
END_MESSAGE_MAP()


// CFileServicePage message handlers

BOOL CFileServicePage::OnInitDialog() 
{
    CBCGPPropertyPage::OnInitDialog();

    return TRUE;
}

void CFileServicePage::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    string temp = Utility::Wstring2String(wstring(m_FileServerHostName));
    m_Evaluate.SetFileServerHostName(temp.c_str());
    m_Evaluate.SetFileServerPort(m_FileServerPort);
    temp = Utility::Wstring2String(wstring(m_ModelHostName));
    m_Evaluate.SetModelHostName(temp.c_str());
    m_Evaluate.SetModelPort(m_ModelPort);
    m_Evaluate.SetRootPath(m_RootPath);
    if (OK != m_Evaluate.Init())
    {
        Utility::PromptErrorMessage(TEXT("文件服务失败."));
    }
}
