// model_doc.h : interface of the CModelDoc class
//


#pragma once

#include "model_ctrl.h"

class CModelDoc : public CDocument
{
protected: // create from serialization only
	CModelDoc();
	DECLARE_DYNCREATE(CModelDoc)

// Attributes
public:
    ModelCtrlList m_ModelCtrlList;

protected:
    UINT32 m_CurrentComponentId;

// Operations
public:
    bool AddModelCtrl(ModelCtrl *modelCtrl);
    bool RemoveModelCtrl(ModelCtrl *modelCtrl);

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CModelDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


