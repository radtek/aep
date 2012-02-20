// model_page.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "model_page.h"

#include "utility.h"

// CModelPage dialog

IMPLEMENT_DYNAMIC(CModelPage, CBCGPPropertyPage)

CModelPage::CModelPage()
	: CBCGPPropertyPage(CModelPage::IDD),
    m_Client(Client::GetInstance())
{

}

CModelPage::~CModelPage()
{
}

void CModelPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelPage, CDialog)
    ON_BN_CLICKED(IDB_TRANSFER, &CModelPage::OnBnClickedTransfer)
    ON_BN_CLICKED(IDB_MODEL, &CModelPage::OnBnClickedModel)
END_MESSAGE_MAP()


// CModelPage message handlers

void CModelPage::OnBnClickedTransfer()
{
    // TODO: Add your control notification handler code here
    if (!m_Client.IsLogined())
    {
        Utility::PromptErrorMessage(TEXT("您尚未登陆."));
        return;
    }

    CString pathName;

    CFileDialog dlg(FALSE, TEXT("mod"), TEXT("Untitiled.mod"), 0, TEXT("Model Files (*.mod)|*.mod|All Files (*.*)|*.*||"));
    if(dlg.DoModal() == IDOK)
    {
        pathName = dlg.GetPathName();
    }
    else
    {
        return;
    }

    RC rc = m_Client.SendModelFile(pathName);

    if (OK != rc)
    {
        Utility::PromptErrorMessage(TEXT("未知错误."));
        return;
    }

    Utility::PromptMessage(TEXT("发送模型文件成功."));
}

void CModelPage::OnBnClickedModel()
{
    // TODO: Add your control notification handler code here
    if (!m_Client.IsLogined())
    {
        Utility::PromptErrorMessage(TEXT("您尚未登陆."));
        return;
    }

    WinExec("model_app.exe", SW_SHOWNORMAL);
}
