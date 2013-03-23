// model_view.cpp : implementation of the CModelView class
//

#include "stdafx.h"
#include "model_app.h"

#include "model_doc.h"
#include "model_view.h"

#include "component_ctrl.h"
#include "internal_algorithm_ctrl.h"
#include "connector_ctrl.h"
#include "hor_poly_connector_ctrl.h"
#include "ver_poly_connector_ctrl.h"

#include "utility.h"
#include "massert.h"

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
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_KEYDOWN()
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

void CModelView::OnDraw(CDC *dc)
{
	CModelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

    // TODO: add draw code for native data here
    ModelCtrlList &modelCtrlList = pDoc->m_ModelCtrlList;
    for (ModelCtrlList::iterator it = modelCtrlList.end();
        it != modelCtrlList.begin();)
    {
        ModelCtrl *modelCtrl = *(--it);
        modelCtrl->Draw(dc);
    }
    
    ConnectorCtrlList &connectorCtrlList = pDoc->m_ConnectorCtrlList;
    for (ConnectorCtrlList::iterator it = connectorCtrlList.end();
        it != connectorCtrlList.begin();)
    {
        ConnectorCtrl *connectorCtrl = *(--it);
        connectorCtrl->Draw(dc);
    }
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

ModelCtrl *CModelView::HitTestModelCtrl(CPoint point)
{
    // Selecting model controls.
    ModelCtrlList &modelCtrlList = GetDocument()->m_ModelCtrlList;
    for (ModelCtrlList::iterator it = modelCtrlList.begin();
        it != modelCtrlList.end(); ++it)
    {
        ModelCtrl *modelCtrl = (*it);
        if (modelCtrl->HitTest(point))
        {
            return modelCtrl;
        }
    }
    return NULL;
}

ConnectorCtrl *CModelView::HitTestConnectorCtrl(CPoint point)
{
    // Selecting connector ctrls.
    ConnectorCtrlList &connectorCtrlList = GetDocument()->m_ConnectorCtrlList;
    for (ConnectorCtrlList::iterator it = connectorCtrlList.begin();
        it != connectorCtrlList.end(); ++it)
    {
        ConnectorCtrl *connectorCtrl = *it;
        if (connectorCtrl->HitTest(point) != ConnectorCtrl::CSM_NONE)
        {
            return connectorCtrl;
        }
    }
    return NULL;
}

// CModelView message handlers

void CModelView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    SetCapture();

    if (GetDocument()->m_CurrentState == CModelDoc::STATE_NEW_COMPONENT)
    {
        ComponentType &info = theApp.m_Platform.GetComponentTypeMap()[GetDocument()->m_CurrentComponentTypeId];
        IComponent *component = info.Factory();
        ModelCtrl *modelCtrl = new ComponentCtrl(component, point);
        GetDocument()->AddModelCtrl(modelCtrl);
        GetDocument()->m_CurrentState = CModelDoc::STATE_NORMAL;
        GetDocument()->UnSelectAll();
        Invalidate();
    }
    else if (GetDocument()->m_CurrentState == CModelDoc::STATE_NEW_INTERNAL_ALGORITHM)
    {
        InternalAlgorithm &internalAlgorithm = theApp.m_Platform.GetInternalAlgorithmMap()[GetDocument()->m_CurrentInternalAlgorithmId];
        ModelCtrl *modelCtrl = new InternalAlgorithmCtrl(&internalAlgorithm, point);
        GetDocument()->AddModelCtrl(modelCtrl);
        GetDocument()->m_CurrentState = CModelDoc::STATE_NORMAL;
        GetDocument()->UnSelectAll();
        Invalidate();
    }
    else if (GetDocument()->m_CurrentState == CModelDoc::STATE_NEW_EXTERNAL_ALGORITHM)
    {
    }
    else if (GetDocument()->m_CurrentState == CModelDoc::STATE_NEW_CONNECTOR)
    {
        ConnectorCtrl *connectorCtrl = NULL;
        if (GetDocument()->m_CurrentConnectorId == ID_CONNECTOR)
        {
            connectorCtrl = new ConnectorCtrl(point);
        }
        else if (GetDocument()->m_CurrentConnectorId == ID_HOR_POLY_CONNECTOR)
        {
            connectorCtrl = new HorPolyConnectorCtrl(point);
        }
        else if (GetDocument()->m_CurrentConnectorId == ID_VER_POLY_CONNECTOR)
        {
            connectorCtrl = new VerPolyConnectorCtrl(point);
        }
        else
        {
            Utility::PromptErrorMessage(TEXT("读取模型文件失败."));
            return;
        }
        GetDocument()->AddConnectorCtrl(connectorCtrl);
        GetDocument()->m_CurrentState = CModelDoc::STATE_NORMAL;
        GetDocument()->UnSelectAll();
        Invalidate();
    }
    else if (GetDocument()->m_CurrentState == CModelDoc::STATE_COMPONENT_SELECTED)
    {
        ConnectorCtrl *connectorCtrl = HitTestConnectorCtrl(point);
        if (connectorCtrl != NULL)
        {
            GetDocument()->UnSelectCurrentModelCtrl();
            GetDocument()->m_CurrentState = CModelDoc::STATE_CONNECTOR_SELECTED;
            GetDocument()->SelectConnectorCtrl(connectorCtrl, point);
        }
        else
        {
            ModelCtrl *modelCtrl = HitTestModelCtrl(point);
            if (modelCtrl != NULL)
            {
                if (modelCtrl != GetDocument()->m_CurrentModelCtrl)
                {
                    GetDocument()->UnSelectCurrentModelCtrl();
                    GetDocument()->SelectModelCtrl(modelCtrl);
                }
            }
            else
            {
                GetDocument()->m_CurrentState = CModelDoc::STATE_NORMAL;
                GetDocument()->UnSelectCurrentModelCtrl();
            }
        }

        Invalidate();
    }
    else if (GetDocument()->m_CurrentState == CModelDoc::STATE_CONNECTOR_SELECTED)
    {
        ConnectorCtrl *connectorCtrl = HitTestConnectorCtrl(point);
        if (connectorCtrl != NULL)
        {
            if (connectorCtrl != GetDocument()->m_CurrentConnectorCtrl)
            {
                GetDocument()->UnSelectCurrentConnectorCtrl();
                GetDocument()->SelectConnectorCtrl(connectorCtrl, point);
            }
            else
            {
                GetDocument()->SelectConnectorCtrl(connectorCtrl, point);
            }
        }
        else
        {
            ModelCtrl *modelCtrl = HitTestModelCtrl(point);
            if (modelCtrl != NULL)
            {
                GetDocument()->UnSelectCurrentConnectorCtrl();
                GetDocument()->m_CurrentState = CModelDoc::STATE_COMPONENT_SELECTED;
                GetDocument()->SelectModelCtrl(modelCtrl);
            }
            else
            {
                GetDocument()->m_CurrentState = CModelDoc::STATE_NORMAL;
                GetDocument()->UnSelectCurrentConnectorCtrl();
            }
        }

        Invalidate();
    }
    else if (GetDocument()->m_CurrentState == CModelDoc::STATE_NORMAL)
    {
        ConnectorCtrl *connectorCtrl = HitTestConnectorCtrl(point);
        if (connectorCtrl != NULL)
        {
            GetDocument()->m_CurrentState = CModelDoc::STATE_CONNECTOR_SELECTED;
            GetDocument()->SelectConnectorCtrl(connectorCtrl, point);
        }
        else
        {
            ModelCtrl *modelCtrl = HitTestModelCtrl(point);
            if (modelCtrl != NULL)
            {
                GetDocument()->m_CurrentState = CModelDoc::STATE_COMPONENT_SELECTED;
                GetDocument()->SelectModelCtrl(modelCtrl);
            }
        }

        Invalidate();
    }

    GetDocument()->m_LastClickPosition = point;
    GetDocument()->m_Moved = false;

    CView::OnLButtonDown(nFlags, point);
}

void CModelView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (!(nFlags & MK_LBUTTON))
    {
        return;
    }

    if (GetDocument()->m_CurrentState == CModelDoc::STATE_COMPONENT_SELECTED)
    {
        CPoint d = point - GetDocument()->m_LastClickPosition;
        GetDocument()->m_CurrentModelCtrl->Move(d);

        Invalidate();
    }

    else if (GetDocument()->m_CurrentState == CModelDoc::STATE_CONNECTOR_SELECTED)
    {
        CPoint d = point - GetDocument()->m_LastClickPosition;
        GetDocument()->m_CurrentConnectorCtrl->Move(d);

        Invalidate();
    }

    GetDocument()->m_LastClickPosition = point;
    GetDocument()->m_Moved = true;

    CView::OnMouseMove(nFlags, point);
}

void CModelView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    ReleaseCapture();

    if (GetDocument()->m_CurrentState == CModelDoc::STATE_CONNECTOR_SELECTED)
    {
        if (GetDocument()->m_Moved)
        {
            GetDocument()->m_CurrentConnectorCtrl->Disconnect();

            ModelCtrl *modelCtrl = HitTestModelCtrl(point);
            if (modelCtrl != NULL)
            {
                GetDocument()->m_CurrentConnectorCtrl->SetAttachPoint(modelCtrl->GetAttachPoint(point));
                GetDocument()->m_CurrentConnectorCtrl->Connect(modelCtrl);
            }
        }

        Invalidate();
    }

    GetDocument()->m_Moved = false;

    CView::OnLButtonUp(nFlags, point);
}

void CModelView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (GetDocument()->m_CurrentState == CModelDoc::STATE_COMPONENT_SELECTED)
    {
        ModelCtrl *modelCtrl = HitTestModelCtrl(point);
        if (modelCtrl != NULL)
        {
            modelCtrl->Config();
            GetDocument()->UnSelectCurrentModelCtrl();
            GetDocument()->SelectModelCtrl(modelCtrl);
        }
        else
        {
            GetDocument()->m_CurrentState = CModelDoc::STATE_NORMAL;
            GetDocument()->UnSelectCurrentModelCtrl();
        }

        Invalidate();
    }

    CView::OnLButtonDblClk(nFlags, point);
}

void CModelView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: Add your message handler code here and/or call default
    switch (nChar)
    {
    case VK_BACK:
    case VK_DELETE:
        if (GetDocument()->m_CurrentState == CModelDoc::STATE_COMPONENT_SELECTED)
        {
            GetDocument()->RemoveCurrentModelCtrl();
            GetDocument()->m_CurrentState = CModelDoc::STATE_NORMAL;
        }
        else if (GetDocument()->m_CurrentState == CModelDoc::STATE_CONNECTOR_SELECTED)
        {
            GetDocument()->RemoveCurrentConnectorCtrl();
            GetDocument()->m_CurrentState = CModelDoc::STATE_NORMAL;
        }
        Invalidate();
        break;
    }

    CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
