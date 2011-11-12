// test_platform_dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test_platform.h"
#include "test_platform_dlg.h"

#include "platform.h"
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
    , m_Platform(Platform::GetInstance())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestPlatformDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMPONENTINFO_LIST, m_ComponentInfoList);
    DDX_Control(pDX, IDC_COMPONENT_LIST, m_ComponentList);
    DDX_Control(pDX, IDC_ALGORITHM_SEL, m_AlgorithmList);
}

BEGIN_MESSAGE_MAP(CTestPlatformDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_NOTIFY(NM_RCLICK, IDC_COMPONENTINFO_LIST, &CTestPlatformDlg::OnNMRclickComponentInfoList)
    ON_NOTIFY(NM_RCLICK, IDC_COMPONENT_LIST, &CTestPlatformDlg::OnNMRclickComponentList)
    ON_BN_CLICKED(IDC_RUN_MODEL, &CTestPlatformDlg::OnBnClickedRunModel)
    ON_BN_CLICKED(IDC_VALIDATE_MODEL, &CTestPlatformDlg::OnBnClickedValidateModel)
    ON_BN_CLICKED(IDC_ALGORITHM_RUN, &CTestPlatformDlg::OnBnClickedAlgorithmRun)
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

    CHECK_RC(m_Platform.Init());

    CHECK_RC(InitComponentInfoList());
    m_ComponentList.SetImageList(&m_ComponentInfoImageList, LVSIL_NORMAL);

    CHECK_RC(InitAlgorithmList());

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

    m_ComponentInfoImageList.Create(32, 32, true, 2, 2);
    for (UINT32 i = 0; i < m_Platform.GetComponentInfoList().size(); ++i)
    {
        m_ComponentInfoImageList.Add((HICON)m_Platform.GetComponentInfoList()[i].iconHandle);//AfxGetApp()->LoadIcon(m_Platform.GetComponentInfoList()[i].iconHandle));
        m_ComponentInfoList.InsertItem(LVIF_TEXT | LVIF_IMAGE, i, (LPCTSTR)m_Platform.GetComponentInfoList()[i].typeName, 0, 0, i, NULL);
    }
    m_ComponentInfoList.SetImageList(&m_ComponentInfoImageList, LVSIL_NORMAL);

    //AfxSetResourceHandle(AfxGetInstanceHandle());

    return OK;
}

RC CTestPlatformDlg::InitAlgorithmList()
{
    RC rc;

    for (UINT32 i = 0; i < m_Platform.GetAlgorithmList().size(); ++i)
    {
        Algorithm algorithm = m_Platform.GetAlgorithmList()[i];
        m_AlgorithmList.AddString(algorithm.GetName().c_str());
    }
    //AfxSetResourceHandle(AfxGetInstanceHandle());

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
    menu.LoadMenu(IDR_TEST_PLATFORM_MENU);
    CMenu *popup = menu.GetSubMenu(0);
    CPoint point;
    GetCursorPos(&point);
    INT32 sel = popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, point.x, point.y, this);
    if (ID_COMPONENTINFO_CREATE == sel)
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

    IComponent *component = m_Platform.GetComponentInfoList()[componentId].factory();
    m_Platform.GetComponentList().push_back(component);

    LPWSTR name;
    CHECK_RC(component->GetName(&name));
    //AfxSetResourceHandle((HINSTANCE)m_DllHandle);
    m_ComponentList.InsertItem(LVIF_TEXT | LVIF_IMAGE, (INT32)m_Platform.GetComponentList().size() - 1, name, 0, 0, componentId, NULL);
    //AfxSetResourceHandle(AfxGetInstanceHandle());

    return rc;
}

void CTestPlatformDlg::OnNMRclickComponentList(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: Add your control notification handler code here
    LPNMITEMACTIVATE item = (LPNMITEMACTIVATE)pNMHDR;
    if (item->iItem < 0)
    {
        return;
    }
    CMenu menu;
    menu.LoadMenu(IDR_TEST_PLATFORM_MENU);
    CMenu *popup = menu.GetSubMenu(1);
    CPoint point;
    GetCursorPos(&point);
    INT32 sel = popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, point.x, point.y, this);
    if (ID_COMPONENT_CONFIG == sel)
    {
        m_Platform.GetComponentList()[item->iItem]->Config();
        LPWSTR name;
        m_Platform.GetComponentList()[item->iItem]->GetName(&name);
        m_ComponentList.SetItemText(item->iItem, 0, name);
    }
    else if (ID_COMPONENT_DELETE == sel)
    {
        DeleteComponent(item->iItem);
    }
    *pResult = 0;
}

RC CTestPlatformDlg::DeleteComponent(UINT32 componentId)
{
    RC rc;

    CHECK_RC(m_Platform.GetComponentList()[componentId]->Destroy());
    m_Platform.GetComponentList().erase(m_Platform.GetComponentList().begin() + componentId);
    m_ComponentList.DeleteItem(componentId);

    return rc;
}

void CTestPlatformDlg::OnBnClickedRunModel()
{
    // TODO: Add your control notification handler code here
    OnBnClickedValidateModel();
    m_Platform.RunModel();
}

void CTestPlatformDlg::OnBnClickedValidateModel()
{
    // TODO: Add your control notification handler code here
    bool valid;
    m_Platform.ValidateModel(valid);
    if (!valid)
    {
        ::MessageBox(NULL, TEXT("模型中存在非法状态"), TEXT("错误"), MB_OK); 
        return;
    }
}

void CTestPlatformDlg::OnBnClickedAlgorithmRun()
{
    // TODO: Add your control notification handler code here
    // IAlgorithm *algorithm = m_Platform.GetAlgorithmList()[m_AlgorithmList.GetCurSel()];
    // algorithm->Run();

    m_Platform.GetAlgorithmList()[0].Run();
}
