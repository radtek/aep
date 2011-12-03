// outputbar.cpp : implementation of the COutputBar class
//

#include "stdafx.h"
#include "model_app.h"
#include "output_bar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 1;
/////////////////////////////////////////////////////////////////////////////
// COutputBar

BEGIN_MESSAGE_MAP(COutputBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(COutputBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBar construction/destruction

COutputBar::COutputBar()
{
	// TODO: add one-time construction code here
}

COutputBar::~COutputBar()
{
}

CBCGPGridRow *COutputBar::CreateNewRow()
{
	CBCGPGridRow *row = m_wndList.CreateRow(m_wndList.GetColumnCount());

	for (UINT32 i = 0; i < m_wndList.GetColumnCount (); ++i)
	{
		row->GetItem(i)->AllowEdit(FALSE);
	}

	return row;
}

void COutputBar::AddEmptyRow()
{
	m_wndList.AddRow(CreateNewRow(), FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// COutputBar message handlers

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create list window.
	// TODO: create your own window here:
	const DWORD dwViewStyle =	
		LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	
	if (!m_wndList.Create (dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Failed to create output view\n");
		return -1;      // fail to create
	}

    m_wndList.SetWholeRowSel(FALSE);
    m_wndList.EnableMarkSortedColumn(FALSE);
	m_wndList.EnableHeader(TRUE, 0);

    m_wndList.InsertColumn (0, _T("A"), 30);
	m_wndList.InsertColumn (1, _T("B"), 80);
	m_wndList.InsertColumn (2, _T("C"), 120);
	m_wndList.InsertColumn (3, _T("D"), 50);
	m_wndList.InsertColumn (4, _T("E"), 80);
	m_wndList.InsertColumn (5, _T("F"), 120);

    AddEmptyRow();

	return 0;
}

void COutputBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	m_wndList.SetWindowPos (NULL, nBorderSize, nBorderSize, 
		cx - 2 * nBorderSize, cy - 2 * nBorderSize,
		SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectList;
	m_wndList.GetWindowRect (rectList);
	ScreenToClient (rectList);

	rectList.InflateRect (1, 1);
	dc.Draw3dRect (rectList,	::GetSysColor (COLOR_3DSHADOW), 
								::GetSysColor (COLOR_3DSHADOW));
}
