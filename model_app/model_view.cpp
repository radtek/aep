// model_view.cpp : implementation of the CModelView class
//

#include "stdafx.h"
#include "model_app.h"

#include "model_doc.h"
#include "model_view.h"

#include "component_ctrl.h"
#include "internal_algorithm_ctrl.h"
#include "connector.h"

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
END_MESSAGE_MAP()

// CModelView construction/destruction

CModelView::CModelView()
:
m_CurrentState(STATE_NORMAL),
m_CurrentComponentTypeId(-1),
m_CurrentModelCtrl(NULL),
m_CurrentInternalAlgorithmId(-1),
m_CurrentConnectorId(-1),
m_CurrentConnector(NULL),
m_Moved(false)
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
    
    ConnectorList &connectorList = pDoc->m_ConnectorList;
    for (ConnectorList::iterator it = connectorList.end();
        it != connectorList.begin();)
    {
        Connector *connector = *(--it);
        connector->Draw(dc);
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

void CModelView::UnSelectCurrentModelCtrl()
{
    m_CurrentModelCtrl->UnSelect();
    m_CurrentModelCtrl = NULL;
}

void CModelView::UnSelectCurrentConnector()
{
    m_CurrentConnector->Select(Connector::CSM_NONE);
    m_CurrentConnector = NULL;
}

void CModelView::UnSelectAll()
{
    m_CurrentComponentTypeId = -1;
    if (m_CurrentModelCtrl != NULL)
    {
        m_CurrentModelCtrl->UnSelect();
        m_CurrentModelCtrl = NULL;
    }

    m_CurrentConnectorId = -1;
    if (m_CurrentConnector != NULL)
    {
        m_CurrentConnector->Select(Connector::CSM_NONE);
    }
}

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

Connector *CModelView::HitTestConnector(CPoint point)
{
    // Selecting connectors.
    ConnectorList &connectorList = GetDocument()->m_ConnectorList;
    for (ConnectorList::iterator it = connectorList.begin();
        it != connectorList.end(); ++it)
    {
        Connector *connector = *it;
        if (connector->HitTest(point) != Connector::CSM_NONE)
        {
            return connector;
        }
    }
    return NULL;
}

void CModelView::SelectModelCtrl(ModelCtrl *modelCtrl)
{
    m_CurrentModelCtrl = modelCtrl;
    m_CurrentModelCtrl->Select();
}

void CModelView::SelectConnector(Connector *connector, CPoint point)
{
    m_CurrentConnector = connector;
    m_CurrentConnector->Select(m_CurrentConnector->HitTest(point));
}

// CModelView message handlers

void CModelView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    SetCapture();

    if (m_CurrentState == STATE_NEW_COMPONENT)
    {
        ComponentType &info = theApp.m_Platform.GetComponentTypeMap()[m_CurrentComponentTypeId];
        IComponent *component = info.Factory();
        ModelCtrl *modelCtrl = new ComponentCtrl(component, point);
        GetDocument()->AddModelCtrl(modelCtrl);
        m_CurrentState = STATE_NORMAL;
        UnSelectAll();
        Invalidate();
    }
    else if (m_CurrentState == STATE_NEW_INTERNAL_ALGORITHM)
    {
        InternalAlgorithm &internalAlgorithm = theApp.m_Platform.GetInternalAlgorithmMap()[m_CurrentInternalAlgorithmId];
        ModelCtrl *modelCtrl = new InternalAlgorithmCtrl(&internalAlgorithm, point);
        GetDocument()->AddModelCtrl(modelCtrl);
        m_CurrentState = STATE_NORMAL;
        UnSelectAll();
        Invalidate();
    }
    else if (m_CurrentState == STATE_NEW_EXTERNAL_ALGORITHM)
    {
    }
    else if (m_CurrentState == STATE_NEW_CONNECTOR)
    {
        Connector *connector = new Connector(point);
        GetDocument()->AddConnector(connector);
        m_CurrentState = STATE_NORMAL;
        UnSelectAll();
        Invalidate();
    }
    else if (m_CurrentState == STATE_COMPONENT_SELECTED)
    {
        Connector *connector = HitTestConnector(point);
        if (connector != NULL)
        {
            UnSelectCurrentModelCtrl();
            m_CurrentState = STATE_CONNECTOR_SELECTED;
            SelectConnector(connector, point);
        }
        else
        {
            ModelCtrl *modelCtrl = HitTestModelCtrl(point);
            if (modelCtrl != NULL)
            {
                if (modelCtrl != m_CurrentModelCtrl)
                {
                    UnSelectCurrentModelCtrl();
                    SelectModelCtrl(modelCtrl);
                }
            }
            else
            {
                m_CurrentState = STATE_NORMAL;
                UnSelectCurrentModelCtrl();
            }
        }

        Invalidate();
    }
    else if (m_CurrentState == STATE_CONNECTOR_SELECTED)
    {
        Connector *connector = HitTestConnector(point);
        if (connector != NULL)
        {
            if (connector != m_CurrentConnector)
            {
                UnSelectCurrentConnector();
                SelectConnector(connector, point);
            }
            else
            {
                SelectConnector(connector, point);
            }
        }
        else
        {
            ModelCtrl *modelCtrl = HitTestModelCtrl(point);
            if (modelCtrl != NULL)
            {
                UnSelectCurrentConnector();
                m_CurrentState = STATE_COMPONENT_SELECTED;
                SelectModelCtrl(modelCtrl);
            }
            else
            {
                m_CurrentState = STATE_NORMAL;
                UnSelectCurrentConnector();
            }
        }

        Invalidate();
    }
    else if (m_CurrentState == STATE_NORMAL)
    {
        Connector *connector = HitTestConnector(point);
        if (connector != NULL)
        {
            m_CurrentState = STATE_CONNECTOR_SELECTED;
            SelectConnector(connector, point);
        }
        else
        {
            ModelCtrl *modelCtrl = HitTestModelCtrl(point);
            if (modelCtrl != NULL)
            {
                m_CurrentState = STATE_COMPONENT_SELECTED;
                SelectModelCtrl(modelCtrl);
            }
        }

        Invalidate();
    }

    m_LastClickPosition = point;
    m_Moved = false;

    CView::OnLButtonDown(nFlags, point);
}

void CModelView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (!(nFlags & MK_LBUTTON))
    {
        return;
    }

    if (m_CurrentState == STATE_COMPONENT_SELECTED)
    {
        CPoint d = point - m_LastClickPosition;
        m_CurrentModelCtrl->Move(d);

        Invalidate();
    }

    else if (m_CurrentState == STATE_CONNECTOR_SELECTED)
    {
        CPoint d = point - m_LastClickPosition;
        m_CurrentConnector->Move(d);

        Invalidate();
    }

    m_LastClickPosition = point;
    m_Moved = true;

    CView::OnMouseMove(nFlags, point);
}

void CModelView::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    ReleaseCapture();

    if (m_CurrentState == STATE_CONNECTOR_SELECTED)
    {
        if (m_Moved)
        {
            m_CurrentConnector->Disconnect();

            ModelCtrl *modelCtrl = HitTestModelCtrl(point);
            if (modelCtrl != NULL)
            {
                m_CurrentConnector->SetAttachPoint(modelCtrl->GetAttachPoint(point));
                m_CurrentConnector->Connect(modelCtrl);
            }
        }

        Invalidate();
    }

    m_Moved = false;

    CView::OnLButtonUp(nFlags, point);
}

void CModelView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (m_CurrentState == STATE_COMPONENT_SELECTED)
    {
        ModelCtrl *modelCtrl = HitTestModelCtrl(point);
        if (modelCtrl != NULL)
        {
            modelCtrl->Config();
            UnSelectCurrentModelCtrl();
            SelectModelCtrl(modelCtrl);
        }
        else
        {
            m_CurrentState = STATE_NORMAL;
            UnSelectCurrentModelCtrl();
        }

        Invalidate();
    }

    CView::OnLButtonDblClk(nFlags, point);
}
