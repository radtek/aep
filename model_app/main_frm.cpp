// main_frm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "model_app.h"

#include "main_frm.h"
#include "model_view.h"

#include "console_dlg.h"
#include "model2.h"
#include "batch.h"
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
	ON_COMMAND_RANGE(ID_COMPONENT_TYPE_BEGIN, ID_COMPONENT_TYPE_END, OnComponentType)
    ON_UPDATE_COMMAND_UI_RANGE(ID_COMPONENT_TYPE_BEGIN, ID_COMPONENT_TYPE_END, OnUpdateComponentTypeUI)
    ON_COMMAND_RANGE(ID_INTERNAL_ALGORITHM_BEGIN, ID_INTERNAL_ALGORITHM_END, OnInternalAlgorithm)
    ON_UPDATE_COMMAND_UI_RANGE(ID_INTERNAL_ALGORITHM_BEGIN, ID_INTERNAL_ALGORITHM_END, OnUpdateInternalAlgorithmUI)
	ON_COMMAND_RANGE(ID_EXTERNAL_ALGORITHM_BEGIN, ID_EXTERNAL_ALGORITHM_END, OnExternalAlgorithm)
    ON_UPDATE_COMMAND_UI_RANGE(ID_EXTERNAL_ALGORITHM_BEGIN, ID_EXTERNAL_ALGORITHM_END, OnUpdateExternalAlgorithmUI)
	ON_COMMAND_RANGE(ID_CONNECTOR_BEGIN, ID_CONNECTOR_END, OnConnector)
    ON_UPDATE_COMMAND_UI_RANGE(ID_CONNECTOR_BEGIN, ID_CONNECTOR_END, OnUpdateConnectorUI)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_VS2008, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_VS2008, OnUpdateAppLook)
    ON_COMMAND(ID_FILE_EXPORT, &CMainFrame::OnFileExport)
    ON_COMMAND(ID_FILE_DRAW, &CMainFrame::OnFileDraw)
    ON_COMMAND(ID_FILE_VALIDATE, &CMainFrame::OnFileValidate)
    ON_COMMAND(ID_FILE_RUN, &CMainFrame::OnFileRun)
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
	lstBasicCommands.AddTail (ID_FILE_EXPORT);
	lstBasicCommands.AddTail (ID_FILE_VALIDATE);
	lstBasicCommands.AddTail (ID_FILE_DRAW);
	lstBasicCommands.AddTail (ID_FILE_RUN);
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

	if (!m_wndOutput.Create (_T("属性设置"), this, CSize (150, 150),
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
    UINT32 componentId = id - ID_COMPONENT_TYPE_BEGIN;
    CModelDoc *doc = DYNAMIC_DOWNCAST(CModelDoc, GetActiveDocument());
    if (doc->m_CurrentState == CModelDoc::STATE_NEW_COMPONENT &&
        componentId == doc->m_CurrentComponentTypeId)
    {
        doc->m_CurrentState = CModelDoc::STATE_NORMAL;
        doc->m_CurrentComponentTypeId = -1;
    }
    else
    {
        doc->m_CurrentState = CModelDoc::STATE_NEW_COMPONENT;
        doc->m_CurrentComponentTypeId = componentId;
    }
}

void CMainFrame::OnUpdateComponentTypeUI(CCmdUI *cmdUI)
{
    CModelDoc *doc = DYNAMIC_DOWNCAST(CModelDoc, GetActiveDocument());
    UINT32 uiId = cmdUI->m_nID - ID_COMPONENT_TYPE_BEGIN;
    if (doc->m_CurrentState == CModelDoc::STATE_NEW_COMPONENT &&
        uiId == doc->m_CurrentComponentTypeId)
    {
        cmdUI->SetCheck();
        return;
    }
    else
    {
        cmdUI->SetCheck(0);
    }
}

void CMainFrame::OnInternalAlgorithm(UINT id)
{
	// TODO: process shortcuts bar commands here...
    UINT32 internalAlgorithmId = id - ID_INTERNAL_ALGORITHM_BEGIN;
    CModelDoc *doc = DYNAMIC_DOWNCAST(CModelDoc, GetActiveDocument());
    if (doc->m_CurrentState == CModelDoc::STATE_NEW_INTERNAL_ALGORITHM &&
        internalAlgorithmId == doc->m_CurrentInternalAlgorithmId)
    {
        doc->m_CurrentState = CModelDoc::STATE_NORMAL;
        doc->m_CurrentInternalAlgorithmId = -1;
    }
    else
    {
        doc->m_CurrentState = CModelDoc::STATE_NEW_INTERNAL_ALGORITHM;
        doc->m_CurrentInternalAlgorithmId = internalAlgorithmId;
    }
}

void CMainFrame::OnUpdateInternalAlgorithmUI(CCmdUI *cmdUI)
{
    CModelDoc *doc = DYNAMIC_DOWNCAST(CModelDoc, GetActiveDocument());
    UINT32 uiId = cmdUI->m_nID - ID_INTERNAL_ALGORITHM_BEGIN;
    if (doc->m_CurrentState == CModelDoc::STATE_NEW_INTERNAL_ALGORITHM &&
        uiId == doc->m_CurrentInternalAlgorithmId)
    {
        cmdUI->SetCheck();
        return;
    }
    else
    {
        cmdUI->SetCheck(0);
    }
}

void CMainFrame::OnExternalAlgorithm(UINT id)
{
}

void CMainFrame::OnUpdateExternalAlgorithmUI(CCmdUI *cmdUI)
{
    CModelDoc *doc = DYNAMIC_DOWNCAST(CModelDoc, GetActiveDocument());
    UINT32 uiId = cmdUI->m_nID - ID_EXTERNAL_ALGORITHM_BEGIN;
    if (doc->m_CurrentState == CModelDoc::STATE_NEW_EXTERNAL_ALGORITHM)
    {
        cmdUI->SetCheck();
        return;
    }
    else
    {
        cmdUI->SetCheck(0);
    }
}

void CMainFrame::OnConnector(UINT id)
{
    UINT32 connectorId = id - ID_CONNECTOR_BEGIN;
    CModelDoc *doc = DYNAMIC_DOWNCAST(CModelDoc, GetActiveDocument());
    if (doc->m_CurrentState == CModelDoc::STATE_NEW_CONNECTOR &&
        connectorId == doc->m_CurrentConnectorId)
    {
        doc->m_CurrentState = CModelDoc::STATE_NORMAL;
        doc->m_CurrentConnectorId = -1;
    }
    else
    {
        doc->m_CurrentState = CModelDoc::STATE_NEW_CONNECTOR;
        doc->m_CurrentConnectorId = connectorId;
    }
}

void CMainFrame::OnUpdateConnectorUI(CCmdUI *cmdUI)
{
    CModelDoc *doc = DYNAMIC_DOWNCAST(CModelDoc, GetActiveDocument());
    UINT32 uiId = cmdUI->m_nID - ID_CONNECTOR_BEGIN;
    if (doc->m_CurrentState == CModelDoc::STATE_NEW_CONNECTOR &&
        uiId == doc->m_CurrentConnectorId)
    {
        cmdUI->SetCheck();
        return;
    }
    else
    {
        cmdUI->SetCheck(0);
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
                pane->AddButton (images.ExtractIcon (interfaceIndex), componentType.TypeName, ID_COMPONENT_TYPE_BEGIN + componentType.TypeId);
            }
        }
        pShortcutsBarContainer->AddTab (pane, interfaceType.InterfaceName, -1, FALSE);
        pane->EnableDocking (CBRS_ALIGN_ANY);
    }

    /*
    InternalAlgorithmMap &internalAlgorithmMap = theApp.m_Platform.GetInternalAlgorithmMap();
    CBCGPOutlookBarPane *internalAlgorithmPane = new CBCGPOutlookBarPane;
    m_PaneList.push_back(internalAlgorithmPane);
    internalAlgorithmPane->Create (&m_wndShortcutsBar, dwDefaultToolbarStyle, ID_PANE_BEGIN + interfaceTypeMap.size());
    internalAlgorithmPane->SetOwner (this);
    internalAlgorithmPane->EnableTextLabels ();
    internalAlgorithmPane->EnableDocking (CBRS_ALIGN_ANY);
    for (InternalAlgorithmMap::iterator it = internalAlgorithmMap.begin();
        it != internalAlgorithmMap.end(); ++it)
    {
        InternalAlgorithm &internalAlgorithm = it->second;
        internalAlgorithmPane->AddButton (images.ExtractIcon (interfaceTypeMap.size()), internalAlgorithm.GetName().c_str(), ID_INTERNAL_ALGORITHM_BEGIN + internalAlgorithm.GetId());
    }
    pShortcutsBarContainer->AddTab (internalAlgorithmPane, InternalAlgorithm::s_ComponentName, -1, FALSE);
    internalAlgorithmPane->EnableDocking (CBRS_ALIGN_ANY);

    // InternalAlgorithmList &internalAlgorithmList = theApp.m_Platform.GetInternalAlgorithmList();
    CBCGPOutlookBarPane *externalAlgorithmPane = new CBCGPOutlookBarPane;
    m_PaneList.push_back(externalAlgorithmPane);
    externalAlgorithmPane->Create (&m_wndShortcutsBar, dwDefaultToolbarStyle, ID_PANE_BEGIN + interfaceTypeMap.size() + 1);
    externalAlgorithmPane->SetOwner (this);
    externalAlgorithmPane->EnableTextLabels ();
    externalAlgorithmPane->EnableDocking (CBRS_ALIGN_ANY);

    pShortcutsBarContainer->AddTab (externalAlgorithmPane, TEXT("外部算法"), -1, FALSE);
    externalAlgorithmPane->EnableDocking (CBRS_ALIGN_ANY);
    */

    CBCGPOutlookBarPane *connectorPane = new CBCGPOutlookBarPane;
    m_PaneList.push_back(connectorPane);
    connectorPane->Create (&m_wndShortcutsBar, dwDefaultToolbarStyle, ID_PANE_BEGIN + interfaceTypeMap.size() + 2);
    connectorPane->SetOwner (this);
    connectorPane->EnableTextLabels ();
    connectorPane->EnableDocking (CBRS_ALIGN_ANY);
    connectorPane->AddButton (images.ExtractIcon (interfaceTypeMap.size() + 2), TEXT("连接线"), ID_CONNECTOR_BEGIN);
    pShortcutsBarContainer->AddTab (connectorPane, TEXT("连接线"), -1, FALSE);
    connectorPane->EnableDocking (CBRS_ALIGN_ANY);

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

void CMainFrame::OnFileExport()
{
    // TODO: Add your command handler code here
    CFileDialog dlg(FALSE, TEXT("mod"), TEXT("Untitiled.mod"), 0, TEXT("Model Files (*.mod)|*.mod|All Files (*.*)|*.*||"));
    if(dlg.DoModal() == IDOK)
    {
        CString pathName = dlg.GetPathName();
        CFile modFile(pathName, CFile::modeWrite | CFile::modeCreate);
        CArchive ar(&modFile, CArchive::store);
        CModelDoc *doc = DYNAMIC_DOWNCAST(CModelDoc, GetActiveDocument());
        if (OK != doc->ExportModel(ar))
        {
            Utility::PromptErrorMessage(TEXT("导出模型文件失败."));
        }
        else
        {
            Utility::PromptMessage(TEXT("导出模型文件成功."));
        }
    }
}

void CMainFrame::OnFileDraw()
{
    CModelDoc *doc = DYNAMIC_DOWNCAST(CModelDoc, GetActiveDocument());
    RC rc = doc->DrawData();
    if (RC::MODEL_MATLAB_ENGINE_ERROR == rc)
    {
        Utility::PromptErrorMessage(TEXT("Matlab引擎未初始化, 无法绘制图形."));
    }
    else if (RC::MODEL_CONNECT_COMPONENT_ERROR == rc)
    {
        Utility::PromptErrorMessage(TEXT("模型中有非法的连接状态."));
    }
    else if (RC::MODEL_NO_PARAM_ERROR == rc)
    {
        Utility::PromptErrorMessage(TEXT("模型中没有可用的数据源."));
    }
    else if (OK != rc)
    {
        Utility::PromptErrorMessage(TEXT("未知错误, 绘制数据图形失败."));
    }
    else
    {
        Utility::PromptMessage(TEXT("绘制数据图形成功."));
    }
}

void CMainFrame::OnFileValidate()
{
    // TODO: Add your command handler code here
    CString pathName;

    CFileDialog dlg(FALSE, TEXT("mod"), TEXT("Untitiled.mod"), 0, TEXT("Model Files (*.mod)|*.mod|All Files (*.*)|*.*||"));
    if(dlg.DoModal() == IDOK)
    {
        pathName = dlg.GetPathName();
    }
    else
    {
        return;
    }
    CFile modFile(pathName, CFile::modeRead);
    CArchive ar(&modFile, CArchive::load);
    Model model;
    RC rc = model.Load(ar);
    if (OK == rc)
    {
        Utility::PromptMessage(TEXT("模型文件解析成功."));
    }
    else
    {
        Utility::PromptErrorMessage(TEXT("模型文件解析失败."));
    }
}

void CMainFrame::OnFileRun()
{
    // TODO: Add your command handler code here
    CModelDoc *doc = DYNAMIC_DOWNCAST(CModelDoc, GetActiveDocument());
    Model2 model = doc->ExportModel();
    RC rc = model.Analyze();
    if (rc == RC::MODEL_GET_ENTRY_ALGORITHM_ERROR || rc == RC::MODEL_NO_ENTRANCE_ALGORITHM_ERROR)
    {
        Utility::PromptErrorMessage(TEXT("缺少入口算法."));
        return;
    }
    else if (rc == RC::MODEL_MULTI_ENTRANCE_ALGORITHM_ERROR)
    {
        Utility::PromptErrorMessage(TEXT("多个入口算法."));
        return;
    }
    else if (rc == RC::MODEL_ALGORITHM_INPUT_ERROR)
    {
        Utility::PromptErrorMessage(TEXT("算法输入错误."));
        return;
    }
    else if (rc == RC::MODEL_ALGORITHM_OUTPUT_ERROR)
    {
        Utility::PromptErrorMessage(TEXT("算法输出错误."));
        return;
    }

    ShowConsoleDlg(model);
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    /*
    rc = model.Run();
    if (OK != rc)
    {
        Utility::PromptErrorMessage(TEXT("模型运行失败."));
    }
    else
    {
        Utility::PromptMessage(TEXT("模型运行成功"));
    }
    */

    /*
    Batch batch(model);
    rc == batch.Parse(TEXT("image.batch"));
    if (rc == RC::BATCH_PARSE_FILE_ERROR)
    {
        Utility::PromptErrorMessage(TEXT("批文件格式错误."));
        return;
    }
    rc = batch.Run();
    if (rc == RC::BATCH_CONFIG_MODEL_ERROR)
    {
        Utility::PromptErrorMessage(TEXT("配置模型错误."));
    }
    else if (rc == RC::BATCH_CONFIG_COMPONENT_ERROR)
    {
        Utility::PromptErrorMessage(TEXT("配置组件错误."));
    }
    */
}
