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

	for (UINT32 i = 0; i < m_wndList.GetColumnCount(); ++i)
	{
		row->GetItem(i)->AllowEdit(FALSE);
	}

	return row;
}

LPCWSTR COutputBar::GetAttributeTypeString(Attribute::AttributeType attributeType)
{
    switch (attributeType)
    {
    case Attribute::TYPE_INT:
        return TEXT("整形");
    case Attribute::TYPE_DOUBLE:
        return TEXT("浮点型");
    case Attribute::TYPE_STRING:
        return TEXT("字符型");
    }
}

CBCGPGridRow *COutputBar::CreateIdRow(IComponent *component)
{
    CBCGPGridRow *row = CreateNewRow();

    row->GetItem(0)->SetValue(TEXT("-"));
    row->GetItem(1)->SetValue(TEXT("组件ID"));
    row->GetItem(2)->SetValue(GetAttributeTypeString(Attribute::TYPE_INT));
    row->GetItem(3)->SetValue(component->GetId());

    return row;
}

CBCGPGridRow *COutputBar::CreateNameRow(IComponent *component)
{
    CBCGPGridRow *row = CreateNewRow();

    row->GetItem(0)->SetValue(TEXT("-"));
    row->GetItem(1)->SetValue(TEXT("组件名称"));
    row->GetItem(2)->SetValue(GetAttributeTypeString(Attribute::TYPE_STRING));
    row->ReplaceItem(3, new CBCGPGridItem(component->GetName().c_str()));

    return row;
}

void COutputBar::InsertAttributeValue(const Attribute &attribute, IComponent *component, CBCGPGridRow *row)
{
    switch (attribute.Type)
    {
    case Attribute::TYPE_INT:
        {
            INT32 value;
            component->GetAttribute(attribute.Id, (void *)(&value));
            row->ReplaceItem(3, new CBCGPGridItem(value));
            break;
        }
    case Attribute::TYPE_DOUBLE:
        {
            double value;
            component->GetAttribute(attribute.Id, (void *)(&value));
            row->ReplaceItem(3, new CBCGPGridItem(value));
            break;
        }
    case Attribute::TYPE_STRING:
        {
            wstring value;
            component->GetAttribute(attribute.Id, (void *)(&value));
            row->ReplaceItem(3, new CBCGPGridItem(value.c_str()));
            break;
        }
    }
}

CBCGPGridRow *COutputBar::CreateAttributeRow(const Attribute &attribute, IComponent *component)
{
    CBCGPGridRow *row = CreateNewRow();

    row->GetItem(0)->SetValue(attribute.Id);
    row->GetItem(1)->SetValue(attribute.Name);
    row->GetItem(2)->SetValue(GetAttributeTypeString(attribute.Type));
    InsertAttributeValue(attribute, component, row);

    return row;
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
		LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE;
	
	if (!m_wndList.Create (dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Failed to create output view\n");
		return -1;      // fail to create
	}

    m_wndList.SetWholeRowSel(FALSE);
    m_wndList.EnableMarkSortedColumn(FALSE);
	m_wndList.EnableHeader(TRUE, 0);

    m_wndList.InsertColumn (0, _T("属性ID"), 100);
	m_wndList.InsertColumn (1, _T("属性名称"), 100);
	m_wndList.InsertColumn (2, _T("属性类型"), 100);
	m_wndList.InsertColumn (3, _T("属性值"), 100);

	m_wndList.AdjustLayout ();

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

void COutputBar::Clear()
{
    m_wndList.RemoveAll();
    m_wndList.Invalidate();
}

void COutputBar::SetComponent(IComponent *component)
{
    m_wndList.AddRow(CreateIdRow(component));
    m_wndList.AddRow(CreateNameRow(component));

    AttributeList attributeList;
    component->GetAttributeList(attributeList);

    for (UINT32 i = 0; i < attributeList.size(); ++i)
    {
        Attribute &attribute = attributeList[i];
        m_wndList.AddRow(CreateAttributeRow(attribute, component));
    }

    m_wndList.AdjustLayout();

    m_wndList.Invalidate();
}
