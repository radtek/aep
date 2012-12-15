// client_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "client_app.h"
#include "client_dlg.h"
#include "utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CClientDlg dialog

IMPLEMENT_DYNAMIC(CClientDlg, CBCGPPropertySheet)

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CBCGPPropertySheet(IDS_CLIENT_DIALOG_CAPTION, pParent)
    , m_Client(Client::GetInstance())
    , m_Evaluate(Evaluate::GetInstance())
{
	SetLook (CBCGPPropertySheet::PropSheetLook_OutlookBar);
	SetIconsList ((globalData.bIsWindows9x || globalData.bIsWindowsNT4) ? IDB_ICONS : IDB_ICONS_HC, 32);

    // AddPage(&m_ServerConfigPage);
    // AddPage(&m_RegisterPage);
    // AddPage(&m_LoginPage);
    // AddPage(&m_ModelPage);

#ifdef __FILE_TRANSFER_PRESENT__
    // AddPage(&m_FileTransferPage);
#endif

    AddPage(&m_FileServicePage);
    AddPage(&m_EvaluatePage);
    AddPage(&m_ImageShowPage);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CClientDlg::~CClientDlg()
{
    m_Client.Shut();
    Client::DestroyInstance();

    m_Evaluate.Shut();
    Evaluate::DestroyInstance();
}

BEGIN_MESSAGE_MAP(CClientDlg, CBCGPPropertySheet)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CBCGPPropertySheet::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
    if (OK != m_Client.Init())
    {
        Utility::PromptErrorMessage(TEXT("初始化客户端失败."));
        return FALSE;
    }
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CBCGPPropertySheet::OnSysCommand(nID, lParam);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

