// outputbar.cpp : implementation of the CAttributeBar class
//

#include "stdafx.h"
#include "model_app.h"
#include "attribute_bar.h"
#include "main_frm.h"
#include "model_view.h"

#include "massert.h"
#include "utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 1;
/////////////////////////////////////////////////////////////////////////////
// CAttributeBar

BEGIN_MESSAGE_MAP(CAttributeBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CAttributeBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttributeBar construction/destruction

CAttributeBar::CAttributeBar()
:
m_AttributeGridCtrl(this),
m_CurrentState(STATE_NONE),
m_CurrentComponent(NULL),
m_CurrentInternalAlgorithm(NULL)
{
	// TODO: add one-time construction code here
}

CAttributeBar::~CAttributeBar()
{
}

CBCGPGridRow *CAttributeBar::CreateNewRow()
{
	CBCGPGridRow *row = m_AttributeGridCtrl.CreateRow(m_AttributeGridCtrl.GetColumnCount());

	for (UINT32 i = 0; i < m_AttributeGridCtrl.GetColumnCount(); ++i)
	{
		row->GetItem(i)->AllowEdit(FALSE);
	}

	return row;
}

CBCGPGridRow *CAttributeBar::CreateComponentIdRow()
{
    CBCGPGridRow *row = CreateNewRow();

    row->GetItem(IC_ID)->SetValue(TEXT("-"));
    if (m_CurrentState == STATE_INTERNAL_ALGORITHM ||
        m_CurrentState == STATE_EXTERNAL_ALGORITHM)
    {
        row->GetItem(IC_NAME)->SetValue(TEXT("算法ID"));
    }
    else
    {
        row->GetItem(IC_NAME)->SetValue(TEXT("组件ID"));
    }
    row->GetItem(IC_TYPE)->SetValue(Utility::AttributeTypeToString(Attribute::TYPE_INT));
    if (m_CurrentState == STATE_COMPONENT)
    {
        row->GetItem(IC_VALUE)->SetValue(m_CurrentComponent->GetId());
    }
    else if (m_CurrentState == STATE_INTERNAL_ALGORITHM)
    {
        row->GetItem(IC_VALUE)->SetValue(m_CurrentInternalAlgorithm->GetId());
    }
    else if (m_CurrentState == STATE_EXTERNAL_ALGORITHM)
    {
        // row->ReplaceItem(IC_VALUE, new CBCGPGridItem(m_CurrentComponent->GetName().c_str()));
    }

    return row;
}

CBCGPGridRow *CAttributeBar::CreateComponentNameRow()
{
    CBCGPGridRow *row = CreateNewRow();

    row->GetItem(IC_ID)->SetValue(TEXT("-"));
    if (m_CurrentState == STATE_INTERNAL_ALGORITHM ||
        m_CurrentState == STATE_EXTERNAL_ALGORITHM)
    {
        row->GetItem(IC_NAME)->SetValue(TEXT("算法名称"));
    }
    else
    {
        row->GetItem(IC_NAME)->SetValue(TEXT("组件名称"));
    }
    row->GetItem(IC_TYPE)->SetValue(Utility::AttributeTypeToString(Attribute::TYPE_STRING));
    if (m_CurrentState == STATE_COMPONENT)
    {
        row->ReplaceItem(IC_VALUE, new CBCGPGridItem(m_CurrentComponent->GetName().c_str()));
    }
    else if (m_CurrentState == STATE_INTERNAL_ALGORITHM)
    {
        row->GetItem(IC_VALUE)->SetValue(m_CurrentInternalAlgorithm->GetName().c_str());
    }
    else if (m_CurrentState == STATE_EXTERNAL_ALGORITHM)
    {
        // row->ReplaceItem(IC_VALUE, new CBCGPGridItem(m_CurrentComponent->GetName().c_str()));
    }

    return row;
}

CBCGPGridRow *CAttributeBar::CreateComponentAttributeRow(const Attribute &attribute)
{
    CBCGPGridRow *row = CreateNewRow();

    row->GetItem(IC_ID)->SetValue(attribute.Id);
    row->GetItem(IC_NAME)->SetValue(attribute.Name);
    row->GetItem(IC_TYPE)->SetValue(Utility::AttributeTypeToString(attribute.Type));
    
    switch (attribute.Type)
    {
    case Attribute::TYPE_INT:
        {
            INT32 value;
            m_CurrentComponent->GetAttribute(attribute.Id, (void *)(&value));
            row->ReplaceItem(IC_VALUE, new CBCGPGridItem(value));
            break;
        }
    case Attribute::TYPE_DOUBLE:
        {
            double value;
            m_CurrentComponent->GetAttribute(attribute.Id, (void *)(&value));
            row->ReplaceItem(IC_VALUE, new CBCGPGridItem(value));
            break;
        }
    case Attribute::TYPE_STRING:
        {
            wstring value;
            m_CurrentComponent->GetAttribute(attribute.Id, (void *)(&value));
            row->ReplaceItem(IC_VALUE, new CBCGPGridItem(value.c_str()));
            break;
        }
    }

    return row;
}

void CAttributeBar::UpdateComponentName()
{
    CBCGPGridRow *row = m_AttributeGridCtrl.GetRow(IR_NAME);
    if (row == NULL)
    {
        return;
    }

    wstring name = row->GetItem(IC_VALUE)->GetValue().bstrVal;
    m_CurrentComponent->SetName(name);
}

void CAttributeBar::UpdateComponentAttribute(int nRow)
{
    CBCGPGridRow *row = m_AttributeGridCtrl.GetRow(nRow);
    if (row == NULL)
    {
        return;
    }

    UINT32 attributeId = row->GetItem(IC_ID)->GetValue().uintVal;
    Attribute::AttributeType type = Utility::StringToAttributeType(row->GetItem(IC_TYPE)->GetValue().bstrVal);
    switch (type)
    {
    case Attribute::TYPE_INT:
        {
            INT32 value = row->GetItem(IC_VALUE)->GetValue().intVal;
            m_CurrentComponent->SetAttribute(attributeId, (void *)(&value));
            break;
        }
    case Attribute::TYPE_DOUBLE:
        {
            double value = row->GetItem(IC_VALUE)->GetValue().dblVal;
            m_CurrentComponent->SetAttribute(attributeId, (void *)(&value));
            break;
        }
    case Attribute::TYPE_STRING:
        {
            wstring value = row->GetItem(IC_VALUE)->GetValue().bstrVal;
            m_CurrentComponent->SetAttribute(attributeId, (void *)(&value));
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// CAttributeBar message handlers

int CAttributeBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create list window.
	// TODO: create your own window here:
	const DWORD dwViewStyle =	
		LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE;
	
	if (!m_AttributeGridCtrl.Create (dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Failed to create output view\n");
		return -1;      // fail to create
	}

    m_AttributeGridCtrl.SetWholeRowSel(FALSE);
    m_AttributeGridCtrl.EnableMarkSortedColumn(FALSE);
	m_AttributeGridCtrl.EnableHeader(TRUE, 0);

    m_AttributeGridCtrl.InsertColumn (IC_ID, _T("属性ID"), 100);
	m_AttributeGridCtrl.InsertColumn (IC_NAME, _T("属性名称"), 100);
	m_AttributeGridCtrl.InsertColumn (IC_TYPE, _T("属性类型"), 100);
	m_AttributeGridCtrl.InsertColumn (IC_VALUE, _T("属性值"), 100);

	m_AttributeGridCtrl.AdjustLayout ();

	return 0;
}

void CAttributeBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	m_AttributeGridCtrl.SetWindowPos (NULL, nBorderSize, nBorderSize, 
		cx - 2 * nBorderSize, cy - 2 * nBorderSize,
		SWP_NOACTIVATE | SWP_NOZORDER);
}

void CAttributeBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectList;
	m_AttributeGridCtrl.GetWindowRect (rectList);
	ScreenToClient (rectList);

	rectList.InflateRect (1, 1);
	dc.Draw3dRect (rectList,	::GetSysColor (COLOR_3DSHADOW), 
								::GetSysColor (COLOR_3DSHADOW));
}

void CAttributeBar::Clear()
{
    m_CurrentState = STATE_NONE;

    m_AttributeGridCtrl.RemoveAll();

    m_AttributeGridCtrl.AdjustLayout();
    m_AttributeGridCtrl.Invalidate();
}

void CAttributeBar::SetComponent(IComponent *component)
{
    m_CurrentState = STATE_COMPONENT;
    m_CurrentComponent = component;

    m_AttributeGridCtrl.AddRow(CreateComponentIdRow());
    m_AttributeGridCtrl.AddRow(CreateComponentNameRow());

    AttributeList attributeList;
    m_CurrentComponent->GetAttributeList(attributeList);

    for (UINT32 i = 0; i < attributeList.size(); ++i)
    {
        Attribute &attribute = attributeList[i];
        m_AttributeGridCtrl.AddRow(CreateComponentAttributeRow(attribute));
    }

    m_AttributeGridCtrl.AdjustLayout();
    m_AttributeGridCtrl.Invalidate();
}

void CAttributeBar::SetInternalAlgorithm(InternalAlgorithm *internalAlgorithm)
{
    m_CurrentState = STATE_INTERNAL_ALGORITHM;
    m_CurrentInternalAlgorithm = internalAlgorithm;

    m_AttributeGridCtrl.AddRow(CreateComponentIdRow());
    m_AttributeGridCtrl.AddRow(CreateComponentNameRow());

    AttributeList attributeList;
    m_CurrentInternalAlgorithm->GetAttributeList(attributeList);

    for (UINT32 i = 0; i < attributeList.size(); ++i)
    {
        Attribute &attribute = attributeList[i];
        m_AttributeGridCtrl.AddRow(CreateComponentAttributeRow(attribute));
    }

    m_AttributeGridCtrl.AdjustLayout();
    m_AttributeGridCtrl.Invalidate();
}

void CAttributeBar::OnItemChanged(CBCGPGridItem* pItem, int nRow, int nColumn)
{
    if (m_CurrentState == STATE_COMPONENT)
    {
        if (nRow == IR_NAME)
        {
            UpdateComponentName();
            ((CMainFrame *)theApp.m_pMainWnd)->GetActiveView()->Invalidate();
        }
        else
        {
            UpdateComponentAttribute(nRow);
        }
    }
    else
    {
    }
}
