// model_page.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "model_page.h"


// CModelPage dialog

IMPLEMENT_DYNAMIC(CModelPage, CBCGPPropertyPage)

CModelPage::CModelPage()
	: CBCGPPropertyPage(CModelPage::IDD)
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
}
