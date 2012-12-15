// file_insertDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "file_insert.h"
#include "file_insertDlg.h"

#include <math.h>

#include "utility.h"

#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cfile_insertDlg 对话框




Cfile_insertDlg::Cfile_insertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cfile_insertDlg::IDD, pParent)
    , m_Dir(_T(""))
    , m_Prefix(_T(""))
    , m_Suffix(_T(""))
    , m_Start(0)
    , m_End(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cfile_insertDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, m_Dir);
    DDX_Text(pDX, IDC_EDIT2, m_Prefix);
    DDX_Text(pDX, IDC_EDIT3, m_Suffix);
    DDX_Text(pDX, IDC_EDIT4, m_Start);
    DDX_Text(pDX, IDC_EDIT5, m_End);
}

BEGIN_MESSAGE_MAP(Cfile_insertDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, &Cfile_insertDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Cfile_insertDlg 消息处理程序

BOOL Cfile_insertDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cfile_insertDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cfile_insertDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR Cfile_insertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cfile_insertDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    UpdateData();

    if (m_Dir == TEXT(""))
    {
        return;
    }

    UINT32 maxDigits = log((double)m_End) + 1;

    for (UINT32 i = m_Start; i <= m_End; ++i)
    {
        wstring fileName(m_Prefix);
        UINT32 digits = log((double)i) + 1;
        for (UINT32 j = 0; j < (maxDigits - digits); ++j)
        {
            fileName += TEXT("0");
        }
        CString fullName(fileName.c_str());
        fullName.AppendFormat(TEXT("%u"), i);
        fileName += m_Suffix;
    }
    // OnOK();
}
