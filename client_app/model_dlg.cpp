// model_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "model_dlg.h"


// CModelDlg dialog

IMPLEMENT_DYNAMIC(CModelDlg, CDialog)

CModelDlg::CModelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModelDlg::IDD, pParent)
{

}

CModelDlg::~CModelDlg()
{
}

void CModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelDlg, CDialog)
END_MESSAGE_MAP()


// CModelDlg message handlers
