// model_doc.cpp : implementation of the CModelDoc class
//

#include "stdafx.h"
#include "model_app.h"

#include "model_doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CModelDoc

IMPLEMENT_DYNCREATE(CModelDoc, CDocument)

BEGIN_MESSAGE_MAP(CModelDoc, CDocument)
END_MESSAGE_MAP()


// CModelDoc construction/destruction

CModelDoc::CModelDoc()
{
	// TODO: add one-time construction code here

}

CModelDoc::~CModelDoc()
{
}

BOOL CModelDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CModelDoc serialization

void CModelDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CModelDoc diagnostics

#ifdef _DEBUG
void CModelDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CModelDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CModelDoc commands
