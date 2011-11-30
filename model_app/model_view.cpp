// model_view.cpp : implementation of the CModelView class
//

#include "stdafx.h"
#include "model_app.h"

#include "model_doc.h"
#include "model_view.h"

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
END_MESSAGE_MAP()

// CModelView construction/destruction

CModelView::CModelView()
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

void CModelView::OnDraw(CDC* /*pDC*/)
{
	CModelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
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
