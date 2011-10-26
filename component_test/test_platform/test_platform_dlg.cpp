// test_platform_dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test_platform.h"
#include "test_platform_dlg.h"

#include "utility.h"

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


// CTestPlatformDlg 对话框




CTestPlatformDlg::CTestPlatformDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestPlatformDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestPlatformDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMPONENTINFO_LIST, m_ComponentInfoList);
    DDX_Control(pDX, IDC_COMPONENT_LIST, m_ComponentList);
}

BEGIN_MESSAGE_MAP(CTestPlatformDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_NOTIFY(NM_RCLICK, IDC_COMPONENTINFO_LIST, &CTestPlatformDlg::OnNMRclickComponentInfoList)
END_MESSAGE_MAP()


// CTestPlatformDlg 消息处理程序

BOOL CTestPlatformDlg::OnInitDialog()
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
    RC rc;
    CHECK_RC(InitComponentInfoList());
    m_ComponentList.SetImageList(&m_ComponentInfoImageList, LVSIL_NORMAL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestPlatformDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestPlatformDlg::OnPaint()
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
HCURSOR CTestPlatformDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

RC CTestPlatformDlg::InitComponentInfoList()
{
    RC rc;

    CHECK_RC(Component::LoadClientComponentDll(TEXT("aircraft_measure.dll"), &m_DllHandle));
    CHECK_RC(Component::RegisterClientComponent(m_DllHandle, m_CComponentInfoList));
    AfxSetResourceHandle((HINSTANCE)m_DllHandle);

    m_ComponentInfoImageList.Create(32, 32, true, 2, 2);
    for (UINT32 i = 0; i < m_CComponentInfoList.size(); ++i)
    {
        m_ComponentInfoImageList.Add(AfxGetApp()->LoadIcon((LPCTSTR)m_CComponentInfoList[i].iconId));
        m_ComponentInfoList.InsertItem(LVIF_TEXT | LVIF_IMAGE, i, (LPCTSTR)m_CComponentInfoList[i].typeName, 0, 0, i, NULL);
    }
    m_ComponentInfoList.SetImageList(&m_ComponentInfoImageList, LVSIL_NORMAL);

    AfxSetResourceHandle(AfxGetInstanceHandle());

    return OK;
}

void CTestPlatformDlg::OnNMRclickComponentInfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    LPNMITEMACTIVATE item = (LPNMITEMACTIVATE)pNMHDR;
    if (item->iItem < 0)
    {
        return;
    }
    CMenu menu;
    menu.LoadMenu(IDR_COMPONENT_MENU);
    CMenu *popup = menu.GetSubMenu(0);
    CPoint point;
    GetCursorPos(&point);
    INT32 sel = popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, point.x, point.y, this);
    if (ID_COMPONENT_CREATE == sel)
    {
        if(OK != InsertComponent(item->iItem))
        {
            Utility::PromptLastErrorMessage();
        }
    }
    *pResult = 0;
}

RC CTestPlatformDlg::InsertComponent(UINT32 componentId)
{
    RC rc;

    IComponent *component = m_CComponentInfoList[componentId].factory();
    LPWSTR name;
    CHECK_RC(component->GetName(&name));

    AfxSetResourceHandle((HINSTANCE)m_DllHandle);
    m_ComponentList.InsertItem(LVIF_TEXT | LVIF_IMAGE, m_CComponentList.size(), name, 0, 0, componentId, NULL);
    AfxSetResourceHandle(AfxGetInstanceHandle());

    return rc;
}
