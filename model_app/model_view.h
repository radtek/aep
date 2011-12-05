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
	CModelDoc* GetDocument() const;

    enum State
    {
        STATE_NORMAL,
        STATE_NEW_COMPONENT,
    } m_CurrentState;

    // New component.
    INT32 m_CurrentComponentTypeId;

    // Normal.
    ModelCtrl *m_CurrentModelCtrl;
    CPoint m_LastClickPosition;

// Operations
public:

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
};

#ifndef _DEBUG  // debug version in model_view.cpp
inline CModelDoc* CModelView::GetDocument() const
   { return reinterpret_cast<CModelDoc*>(m_pDocument); }
#endif

