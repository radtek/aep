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
    ON_BN_CLICKED(IDOK, &CModelPage::OnBnClickedOk)
END_MESSAGE_MAP()


// CModelPage message handlers

void CModelPage::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
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

    if (!m_Client.IsLogined())
    {
        Utility::PromptErrorMessage(TEXT("����δ��½."));
        return;
    }

    RC rc = m_Client.SendModelFile(pathName);

    if (OK != rc)
    {
        Utility::PromptErrorMessage(TEXT("δ֪����."));
        return;
    }

    Utility::PromptMessage(TEXT("����ģ���ļ��ɹ�."));
}
