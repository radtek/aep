// model_doc.h : interface of the CModelDoc class
//


#pragma once

#include "interfaces.h"

class CModelDoc : public CDocument
{
protected: // create from serialization only
	CModelDoc();
	DECLARE_DYNCREATE(CModelDoc)

// Attributes
public:
    ComponentList m_ComponentList;

// Operations
public:

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


