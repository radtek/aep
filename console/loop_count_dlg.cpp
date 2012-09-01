// loop_count_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "console.h"
#include "loop_count_dlg.h"


// CLoopCountDlg dialog

IMPLEMENT_DYNAMIC(CLoopCountDlg, CDialog)

CLoopCountDlg::CLoopCountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoopCountDlg::IDD, pParent)
    , m_LoopCount(1)
{

}

CLoopCountDlg::~CLoopCountDlg()
{
}

void CLoopCountDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_LOOP_COUNT_TEXT, m_LoopCount);
}


BEGIN_MESSAGE_MAP(CLoopCountDlg, CDialog)
END_MESSAGE_MAP()


// CLoopCountDlg message handlers
