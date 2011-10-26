// test_platform_dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test_platform.h"
#include "test_platform_dlg.h"

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
    CHECK_RC(InitComponentInfoList());
    m_ComponentList.SetImageList(&m_ComponentInfoImageList, LVSIL_NORMAL);

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
