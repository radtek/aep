// model_view.h : interface of the CModelView class
//


#pragma once

#include "model_doc.h"

class CModelView : public CView
{
protected: // create from serialization only
	CModelView();
	DECLARE_DYNCREATE(CModelView)

// Attributes
public:
    static const UINT32 s_Threshold = 5;

	CModelDoc* GetDocument() const;

    enum State
    {
        STATE_NORMAL,
        STATE_NEW_COMPONENT,
        STATE_NEW_INTERNAL_ALGORITHM,
        STATE_NEW_EXTERNAL_ALGORITHM,
        STATE_NEW_CONNECTOR,
        STATE_COMPONENT_SELECTED,
        STATE_CONNECTOR_SELECTED,
    } m_CurrentState;

    // New component.
    INT32 m_CurrentComponentTypeId;
    ModelCtrl *m_CurrentModelCtrl;

    // New internal algorithm.
    INT32 m_CurrentInternalAlgorithmId;

    // New connector.
    INT32 m_CurrentConnectorId;
    Connector *m_CurrentConnector;

    // Normal.
    CPoint m_LastClickPosition;
    bool m_Moved;

// Operations
public:
    ModelCtrl *HitTestModelCtrl(CPoint point);
    Connector *HitTestConnector(CPoint point);
    void SelectModelCtrl(ModelCtrl *modelCtrl);
    void SelectConnector(Connector *connector, CPoint point);
    void UnSelectCurrentModelCtrl();
    void UnSelectCurrentConnector();
    void UnSelectAll();

// Overrides
	public:
	virtual void OnDraw(CDC *pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CModelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in model_view.cpp
inline CModelDoc* CModelView::GetDocument() const
   { return reinterpret_cast<CModelDoc*>(m_pDocument); }
#endif

