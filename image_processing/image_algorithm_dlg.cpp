// image_algorithm_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "image_algorithm_dlg.h"


// CImageAlgorithmDlg dialog

IMPLEMENT_DYNAMIC(CImageAlgorithmDlg, CDialog)

CImageAlgorithmDlg::CImageAlgorithmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageAlgorithmDlg::IDD, pParent)
    , m_Width1(0)
    , m_Height1(0)
    , m_Width2(0)
    , m_Height2(0)
    , m_Width3(0)
    , m_Height3(0)
    , m_Width4(0)
    , m_Height4(0)
    , m_Width5(0)
    , m_Height5(0)
    , m_Factor1(0)
    , m_Factor2(0)
    , m_Factor3(0)
    , m_Factor4(0)
    , m_Factor5(0)
    , m_Name(_T(""))
    , m_FromId(0)
    , m_DllFileName(_T(""))
    , m_FuncName(_T(""))
{

}

CImageAlgorithmDlg::~CImageAlgorithmDlg()
{
}

void CImageAlgorithmDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_WIDTH1, m_Width1);
    DDX_Text(pDX, IDC_HEIGHT1, m_Height1);
    DDX_Text(pDX, IDC_WIDTH2, m_Width2);
    DDX_Text(pDX, IDC_HEIGHT2, m_Height2);
    DDX_Text(pDX, IDC_WIDTH3, m_Width3);
    DDX_Text(pDX, IDC_HEIGHT3, m_Height3);
    DDX_Text(pDX, IDC_WIDTH4, m_Width4);
    DDX_Text(pDX, IDC_HEIGHT4, m_Height4);
    DDX_Text(pDX, IDC_WIDTH5, m_Width5);
    DDX_Text(pDX, IDC_HEIGHT5, m_Height5);
    DDX_Text(pDX, IDC_FACTOR1, m_Factor1);
    DDX_Text(pDX, IDC_FACTOR2, m_Factor2);
    DDX_Text(pDX, IDC_FACTOR3, m_Factor3);
    DDX_Text(pDX, IDC_FACTOR4, m_Factor4);
    DDX_Text(pDX, IDC_FACTOR5, m_Factor5);
    DDX_Text(pDX, IDC_NAME, m_Name);
    DDX_Text(pDX, IDC_FROM_ID, m_FromId);
    DDX_Text(pDX, IDC_DLL_FILE_NAME, m_DllFileName);
    DDX_Text(pDX, IDC_FUNC_NAME, m_FuncName);
}


BEGIN_MESSAGE_MAP(CImageAlgorithmDlg, CDialog)
END_MESSAGE_MAP()


// CImageAlgorithmDlg message handlers
