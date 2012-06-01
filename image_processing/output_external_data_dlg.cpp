// output_external_data_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "output_external_data_dlg.h"


// COutputExternalDataDlg dialog

IMPLEMENT_DYNAMIC(COutputExternalDataDlg, CDialog)

COutputExternalDataDlg::COutputExternalDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COutputExternalDataDlg::IDD, pParent)
    , m_OutputId1(0)
    , m_OutputId2(0)
    , m_OutputId3(0)
    , m_OutputId4(0)
    , m_OutputId5(0)
    , m_Width1(0)
    , m_Width2(0)
    , m_Width3(0)
    , m_Width4(0)
    , m_Width5(0)
    , m_Height1(0)
    , m_Height2(0)
    , m_Height3(0)
    , m_Height4(0)
    , m_Height5(0)
    , m_FilePath1(_T(""))
    , m_FilePath2(_T(""))
    , m_FilePath3(_T(""))
    , m_FilePath4(_T(""))
    , m_FilePath5(_T(""))
{

}

COutputExternalDataDlg::~COutputExternalDataDlg()
{
}

void COutputExternalDataDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_OUTPUT_ID1, m_OutputId1);
    DDX_Text(pDX, IDC_OUTPUT_ID2, m_OutputId2);
    DDX_Text(pDX, IDC_OUTPUT_ID3, m_OutputId3);
    DDX_Text(pDX, IDC_OUTPUT_ID4, m_OutputId4);
    DDX_Text(pDX, IDC_OUTPUT_ID5, m_OutputId5);
    DDX_Text(pDX, IDC_WIDTH1, m_Width1);
    DDX_Text(pDX, IDC_WIDTH2, m_Width2);
    DDX_Text(pDX, IDC_WIDTH3, m_Width3);
    DDX_Text(pDX, IDC_WIDTH4, m_Width4);
    DDX_Text(pDX, IDC_WIDTH5, m_Width5);
    DDX_Text(pDX, IDC_HEIGHT1, m_Height1);
    DDX_Text(pDX, IDC_HEIGHT2, m_Height2);
    DDX_Text(pDX, IDC_HEIGHT3, m_Height3);
    DDX_Text(pDX, IDC_HEIGHT4, m_Height4);
    DDX_Text(pDX, IDC_HEIGHT5, m_Height5);
    DDX_Text(pDX, IDC_FILE_PATH1, m_FilePath1);
    DDX_Text(pDX, IDC_FILE_PATH2, m_FilePath2);
    DDX_Text(pDX, IDC_FILE_PATH3, m_FilePath3);
    DDX_Text(pDX, IDC_FILE_PATH4, m_FilePath4);
    DDX_Text(pDX, IDC_FILE_PATH5, m_FilePath5);
}


BEGIN_MESSAGE_MAP(COutputExternalDataDlg, CDialog)
END_MESSAGE_MAP()


// COutputExternalDataDlg message handlers
