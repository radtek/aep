// outputbar.h : interface of the CAttributeBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "interfaces.h"

#include "attribute_grid_ctrl.h"

class CAttributeBar : public CBCGPDockingControlBar
{
public:
	CAttributeBar();

// Attributes
protected:
    enum State
    {
        STATE_NONE,
        STATE_COMPONENT,
        STATE_ALGORITHM,
    } m_CurrentState;

    // Component.
    IComponent *m_CurrentComponent;

    // Grid ctrl.
    enum ItemColumn
    {
        IC_ID = 0,
        IC_NAME,
        IC_TYPE,
        IC_VALUE,
    };

    enum ItemRow
    {
        IR_ID = 0,
        IR_NAME,
    };

	CAttributeGridCtrl m_AttributeGridCtrl;

// Operations
protected:
    CBCGPGridRow *CreateNewRow();

    CBCGPGridRow *CreateComponentIdRow();
    CBCGPGridRow *CreateComponentNameRow();

    CBCGPGridRow *CreateComponentAttributeRow(const Attribute &attribute);

    void UpdateComponentName();
    void UpdateComponentAttribute(int nRow);

public:
    void Clear();
    void SetComponent(IComponent *component);
    void OnItemChanged(CBCGPGridItem* pItem, int nRow, int nColumn);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttributeBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAttributeBar();

// Generated message map functions
protected:
	//{{AFX_MSG(CAttributeBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
