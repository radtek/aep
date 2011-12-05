// main_frm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "model_app.h"

#include "main_frm.h"
#include "model_view.h"

#include "utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)

const int  iMaxUserToolbars		= 10;
const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_COMMAND_RANGE(ID_COMPONENT_INFO_BEGIN, ID_COMPONENT_INFO_END, OnComponentType)
    ON_UPDATE_COMMAND_UI_RANGE(ID_COMPONENT_INFO_BEGIN, ID_COMPONENT_INFO_END, OnUpdateComponentTypeUI)
	ON_COMMAND_RANGE(ID_ALGORITHM_BEGIN, ID_ALGORITHM_END, OnAlgorithm)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_VS2008, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_VS2008, OnUpdateAppLook)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{

	m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_2007);
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

CAttributeBar &CMainFrame::GetAttributeBar()
{
    return m_wndOutput;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	OnAppLook (m_nAppLook);

	// VISUAL_MANAGER
	
	if (CBCGPToolBar::GetUserImages () == NULL)
	{
		// Load toolbar user images:
		if (!m_UserImages.Load (_T(".\\UserImages.bmp")))
		{
			TRACE(_T("Failed to load user images\n"));
		}
		else
		{
			CBCGPToolBar::SetUserImages (&m_UserImages);
		}
	}

	CBCGPToolBar::EnableQuickCustomization ();


	// TODO: Define your own basic commands. Be sure, that each pulldown 
	// menu have at least one basic command.

	CList<UINT, UINT>	lstBasicCommands;

	lstBasicCommands.AddTail (ID_VIEW_TOOLBARS);
	lstBasicCommands.AddTail (ID_FILE_NEW);
	lstBasicCommands.AddTail (ID_FILE_OPEN);
	lstBasicCommands.AddTail (ID_FILE_SAVE);
	lstBasicCommands.AddTail (ID_FILE_PRINT);
	lstBasicCommands.AddTail (ID_APP_EXIT);
	lstBasicCommands.AddTail (ID_EDIT_CUT);
	lstBasicCommands.AddTail (ID_EDIT_PASTE);
	lstBasicCommands.AddTail (ID_EDIT_UNDO);
	lstBasicCommands.AddTail (ID_RECORD_NEXT);
	lstBasicCommands.AddTail (ID_RECORD_LAST);
	lstBasicCommands.AddTail (ID_APP_ABOUT);
	lstBasicCommands.AddTail (ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail (ID_VIEW_CUSTOMIZE);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2000);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_XP);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2003);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_VS2005);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_WIN_XP);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007_1);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007_2);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007_3);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_VS2008);

	CBCGPToolBar::SetBasicCommands (lstBasicCommands);

	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	// Detect color depth. 256 color toolbars can be used in the
	// high or true color modes only (bits per pixel is > 8):
	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 8;

	UINT uiToolbarHotID = bIsHighColor ? IDB_TOOLBAR256 : 0;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, FALSE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndOutput.Create (_T("��������"), this, CSize (150, 150),
		TRUE /* Has gripper */, ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}

	CString strMainToolbarTitle;
	strMainToolbarTitle.LoadString (IDS_MAIN_TOOLBAR);
	m_wndToolBar.SetWindowText (strMainToolbarTitle);

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);

	//------------------------------------------------------------------
	// Outlook bar will be created at left, so temporary disable docking
	// at the left side:
	//------------------------------------------------------------------
	EnableDocking (CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	if (!CreateShortcutsBar ())
	{
		TRACE0("Failed to create shortcuts bar\n");
		return -1;      // fail to create
	}

	//----------------------------------------------------
	// Outlook bar is created and docking on the left side
	// should be allowed.
	//----------------------------------------------------
	EnableDocking (CBRS_ALIGN_LEFT);
	EnableAutoHideBars(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndOutput);


	m_wndToolBar.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));

	// Allow user-defined toolbars operations:
	InitUserToobars (NULL,
					uiFirstUserToolBarId,
					uiLastUserToolBarId);

	// Enable control bar context menu (list of bars + customize command):
	EnableControlBarMenu (	
		TRUE,				// Enable
		ID_VIEW_CUSTOMIZE, 	// Customize command ID
		_T("Customize..."),	// Customize command text
		ID_VIEW_TOOLBARS);	// Menu items with this ID will be replaced by
							// toolbars menu

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CBCGPFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers




void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */);

	pDlgCust->EnableUserDefinedToolbars ();
	pDlgCust->Create ();
}

afx_msg LRESULT CMainFrame::OnToolbarReset(WPARAM /*wp*/,LPARAM)
{
	// TODO: reset toolbar with id = (UINT) wp to its initial state:
	//
	// UINT uiToolBarId = (UINT) wp;
	// if (uiToolBarId == IDR_MAINFRAME)
	// {
	//		do something with m_wndToolBar
	// }

	return 0;
}

void CMainFrame::OnComponentType(UINT id)
{
	// TODO: process shortcuts bar commands here...
    UINT32 componentId = id - ID_COMPONENT_INFO_BEGIN;
    CModelView *view = DYNAMIC_DOWNCAST(CModelView, GetActiveView());
    if (view->m_CurrentState == CModelView::STATE_NEW_COMPONENT &&
        componentId == view->m_CurrentComponentTypeId)
    {
        view->m_CurrentState = CModelView::STATE_NORMAL;
        view->m_CurrentComponentTypeId = -1;
    }
    else
    {
        view->m_CurrentState = CModelView::STATE_NEW_COMPONENT;
        view->m_CurrentComponentTypeId = componentId;
    }
}

void CMainFrame::OnUpdateComponentTypeUI(CCmdUI *cmdUI)
{
    UINT32 componentId = cmdUI->m_nID - ID_COMPONENT_INFO_BEGIN;
    CModelView *view = DYNAMIC_DOWNCAST(CModelView, GetActiveView());
    if (view->m_CurrentState == CModelView::STATE_NEW_COMPONENT &&
        componentId == view->m_CurrentComponentTypeId)
    {
        cmdUI->SetCheck();
    }
    else
    {
        cmdUI->SetCheck(0);
    }
}

void CMainFrame::OnAlgorithm(UINT id)
{
	// TODO: process shortcuts bar commands here...
    UINT32 algorithmId = id - ID_ALGORITHM_BEGIN;
    AlgorithmList &algorithmList = theApp.m_Platform.GetAlgorithmList();
    for (UINT32 i = 0; i < algorithmList.size(); ++i)
    {
        Algorithm &algorithm = algorithmList[i];
        if (algorithm.GetId() == algorithmId)
        {
            Utility::PromptMessage(algorithm.GetName().c_str());
        }
    }
}

BOOL CMainFrame::CreateShortcutsBar ()
{
	CBCGPOutlookWnd::EnableAnimation ();

	const int nInitialWidth = 150;
	const CString strCaption = _T("Shortcuts");

	if (!m_wndShortcutsBar.Create (strCaption, this, 
		CRect (0, 0, nInitialWidth, nInitialWidth), 
		ID_VIEW_OUTLOOKBAR, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE;
	}

	CBCGPOutlookWnd *pShortcutsBarContainer = DYNAMIC_DOWNCAST (CBCGPOutlookWnd, 
							m_wndShortcutsBar.GetUnderlinedWindow ());
	if (m_ShortcutsBarContainer == NULL)
	{
		TRACE0("Cannot get outlook bar container\n");
		return FALSE;
	}

	CImageList images;
	images.Create (IDB_SHORTCUTS, 32, 0, RGB (255, 0, 255));

    InterfaceTypeMap &interfaceTypeMap = theApp.m_Platform.GetInterfaceTypeMap();
    ComponentTypeMap &componentTypeMap = theApp.m_Platform.GetComponentTypeMap();
    UINT32 interfaceIndex = 0;
    for (InterfaceTypeMap::iterator interfaceIt = interfaceTypeMap.begin();
        interfaceIt != interfaceTypeMap.end(); ++interfaceIt, ++interfaceIndex)
    {
        InterfaceType &interfaceType = interfaceIt->second;
        CBCGPOutlookBarPane	*pane = new CBCGPOutlookBarPane;
        m_PaneList.push_back(pane);
        pane->Create (&m_wndShortcutsBar, dwDefaultToolbarStyle, ID_PANE_BEGIN + interfaceIndex);
    	pane->SetOwner (this);
    	pane->EnableTextLabels ();
	    pane->EnableDocking (CBRS_ALIGN_ANY);

        for (ComponentTypeMap::iterator componentIt = componentTypeMap.begin();
            componentIt != componentTypeMap.end(); ++componentIt)
        {
            ComponentType &componentType = componentIt->second;
            if (interfaceType.InterfaceId == componentType.InterfaceId)
            {
                pane->AddButton (images.ExtractIcon (interfaceIndex), componentType.TypeName, ID_COMPONENT_INFO_BEGIN + componentType.TypeId);
            }
        }
        pShortcutsBarContainer->AddTab (pane, interfaceType.InterfaceName, -1, FALSE);
        pane->EnableDocking (CBRS_ALIGN_ANY);
    }

    AlgorithmList &algorithmList = theApp.m_Platform.GetAlgorithmList();
    CBCGPOutlookBarPane *pane = new CBCGPOutlookBarPane;
    m_PaneList.push_back(pane);
    pane->Create (&m_wndShortcutsBar, dwDefaultToolbarStyle, ID_PANE_BEGIN + interfaceTypeMap.size());
    pane->SetOwner (this);
    pane->EnableTextLabels ();
    pane->EnableDocking (CBRS_ALIGN_ANY);
    for (UINT32 i = 0; i < algorithmList.size(); ++i)
    {
        Algorithm &algorithm = algorithmList[i];
        pane->AddButton (images.ExtractIcon (interfaceTypeMap.size()), algorithm.GetName().c_str(), ID_ALGORITHM_BEGIN + algorithm.GetId());
    }
    pShortcutsBarContainer->AddTab (pane, TEXT("�㷨"), -1, FALSE);
    pane->EnableDocking (CBRS_ALIGN_ANY);

	return TRUE;
}

void CMainFrame::OnAppLook(UINT id)
{
	CBCGPDockManager::SetDockMode (BCGP_DT_SMART);

	m_nAppLook = id;

	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	switch (m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2000:
		// enable Office 2000 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager));
		break;

	case ID_VIEW_APPLOOK_XP:
		// enable Office XP look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		// enable Windows XP look (in other OS Office XP look will be used):
		CBCGPWinXPVisualManager::m_b3DTabsXPTheme = TRUE;
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		break;

	case ID_VIEW_APPLOOK_2003:
		// enable Office 2003 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007:
	case ID_VIEW_APPLOOK_2007_1:
	case ID_VIEW_APPLOOK_2007_2:
	case ID_VIEW_APPLOOK_2007_3:
		// enable Office 2007 look:
		switch (m_nAppLook)
		{
		case ID_VIEW_APPLOOK_2007:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_2007_1:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_2007_2:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
			break;

		case ID_VIEW_APPLOOK_2007_3:
			CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);
			break;
		}

		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2005:
		// enable VS 2005 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2008:
		// enable VS 2008 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2008));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;
	}

	CBCGPDockManager* pDockManager = GetDockManager ();
	if (pDockManager != NULL)
	{
		ASSERT_VALID (pDockManager);
		pDockManager->AdjustBarFrames ();
	}

	CBCGPTabbedControlBar::ResetTabs ();

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

	theApp.WriteInt (_T("ApplicationLook"), m_nAppLook);
}

void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nAppLook == pCmdUI->m_nID);
}
 // RIBBON_APP
