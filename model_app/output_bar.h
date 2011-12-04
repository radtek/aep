// outputbar.h : interface of the COutputBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "interfaces.h"

class COutputBar : public CBCGPDockingControlBar
{
public:
	COutputBar();

// Attributes
protected:

	CBCGPGridCtrl	m_wndList;

    CBCGPGridRow *CreateNewRow();
    LPCWSTR GetAttributeTypeString(Attribute::AttributeType attributeType);
    CBCGPGridRow *CreateIdRow(IComponent *component);
    CBCGPGridRow *CreateNameRow(IComponent *component);
    void InsertAttributeValue(const Attribute &attribute, IComponent *component, CBCGPGridRow *row);
    CBCGPGridRow *CreateAttributeRow(const Attribute &attribute, IComponent *component);

// Operations
public:
    void Clear();
    void SetComponent(IComponent *component);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputBar();

// Generated message map functions
protected:
	//{{AFX_MSG(COutputBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
