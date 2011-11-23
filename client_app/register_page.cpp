// register_page.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "register_page.h"


// CRegisterPage dialog

IMPLEMENT_DYNAMIC(CRegisterPage, CBCGPPropertyPage)

CRegisterPage::CRegisterPage()
	: CBCGPPropertyPage(CRegisterPage::IDD)
{

}

CRegisterPage::~CRegisterPage()
{
}

void CRegisterPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegisterPage, CPropertyPage)
END_MESSAGE_MAP()


// CRegisterPage message handlers

BOOL CRegisterPage::OnInitDialog() 
{
    CBCGPPropertyPage::OnInitDialog();

    return TRUE;
}