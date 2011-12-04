// model_view.cpp : implementation of the CModelView class
//

#include "stdafx.h"
#include "model_app.h"

#include "model_doc.h"
#include "model_view.h"

#include "component_ctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CModelView

IMPLEMENT_DYNCREATE(CModelView, CView)

BEGIN_MESSAGE_MAP(CModelView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CModelView construction/destruction

CModelView::CModelView()
:
m_CurrentState(STATE_NORMAL),
m_CurrentComponentTypeId(-1)
{
	// TODO: add construction code here

}

CModelView::~CModelView()
{
}

BOOL CModelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CModelView drawing

void CModelView::OnDraw(CDC *dc)
{
	CModelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
    GetDocument()->OnDraw(dc);
}


// CModelView printing

void CModelView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CModelView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CModelView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CModelView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CModelView diagnostics

#ifdef _DEBUG
void CModelView::AssertValid() const
{
	CView::AssertValid();
}

void CModelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CModelDoc* CModelView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CModelDoc)));
	return (CModelDoc*)m_pDocument;
}
#endif //_DEBUG


// CModelView message handlers

void CModelView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (m_CurrentState == STATE_NEW_COMPONENT)
    {
        ComponentType &info = theApp.m_Platform.GetComponentTypeMap()[m_CurrentComponentTypeId];
        IComponent *component = info.Factory();
        ModelCtrl *modelCtrl = new ComponentCtrl(component, point);
        GetDocument()->AddModelCtrl(modelCtrl);
        m_CurrentComponentTypeId = -1;
        m_CurrentState = STATE_NORMAL;
        Invalidate();
    }
    else if (m_CurrentState == STATE_NORMAL)
    {
        GetDocument()->OnLButtonDown(nFlags, point);
        Invalidate();
    }

    CView::OnLButtonDown(nFlags, point);
}

void CModelView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (nFlags & MK_LBUTTON)
    {
        if (m_CurrentState == STATE_NORMAL)
        {
            GetDocument()->OnMouseMove(nFlags, point);
            Invalidate();
        }
    }

    CView::OnMouseMove(nFlags, point);
}
