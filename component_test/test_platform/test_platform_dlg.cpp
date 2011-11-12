// test_platform_dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test_platform.h"
#include "test_platform_dlg.h"

#include "platform.h"
#include "utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTestPlatformDlg �Ի���




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


// CTestPlatformDlg ��Ϣ�������

BOOL CTestPlatformDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    RC rc;

    CHECK_RC(m_Platform.Init());

    CHECK_RC(InitComponentInfoList());
    m_ComponentList.SetImageList(&m_ComponentInfoImageList, LVSIL_NORMAL);

    CHECK_RC(InitAlgorithmList());

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestPlatformDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
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
        ::MessageBox(NULL, TEXT("ģ���д��ڷǷ�״̬"), TEXT("����"), MB_OK); 
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
