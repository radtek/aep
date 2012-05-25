// console_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "console.h"
#include "console_dlg.h"


// CConsoleDlg dialog

IMPLEMENT_DYNAMIC(CConsoleDlg, CDialog)

CConsoleDlg::CConsoleDlg(Model &model, CWnd* pParent /*=NULL*/)
	: CDialog(CConsoleDlg::IDD, pParent)
    , m_Model(model)
    , m_ModelCtrl(model)
{

}

CConsoleDlg::~CConsoleDlg()
{
}

void CConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MODEL_CTRL, m_ModelCtrl);
}


BEGIN_MESSAGE_MAP(CConsoleDlg, CDialog)
END_MESSAGE_MAP()


// CConsoleDlg message handlers

void __declspec(dllexport) ShowConsoleDlg(Model &model)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CConsoleDlg dlg(model);
    dlg.DoModal();
}