// model_doc.cpp : implementation of the CModelDoc class
//

#include "stdafx.h"
#include "model_app.h"

#include "model_doc.h"

#include "component_ctrl.h"
#include "internal_algorithm_ctrl.h"
#include "connector.h"

#include "utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CModelDoc

IMPLEMENT_DYNCREATE(CModelDoc, CDocument)

BEGIN_MESSAGE_MAP(CModelDoc, CDocument)
END_MESSAGE_MAP()


// CModelDoc construction/destruction

CModelDoc::CModelDoc()
:
m_CurrentComponentId(0)
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
        ar << m_ModelCtrlList.size();

        for (ModelCtrlList::iterator it = m_ModelCtrlList.begin();
            it != m_ModelCtrlList.end(); ++it)
        {
            ModelCtrl *modelCtrl = (*it);
            modelCtrl->Save(ar);
        }

        ar << m_ConnectorList.size();

        for (ConnectorList::iterator it = m_ConnectorList.begin();
            it != m_ConnectorList.end(); ++it)
        {
            Connector *connector = (*it);
            connector->Save(ar);
        }

        ar << m_CurrentComponentId;
	}
	else
	{
		// TODO: add loading code here
        UINT32 modelCtrlListSize = 0;
        ar >> modelCtrlListSize;

        for (UINT32 i = 0; i < modelCtrlListSize; ++i)
        {
            UINT32 modelCtrlId;
            ar >> modelCtrlId;

            ModelCtrl *modelCtrl = NULL;

            if (modelCtrlId == ComponentCtrl::s_ModelCtrlId)
            {
                modelCtrl = new ComponentCtrl();
                modelCtrl->Load(ar);
            }
            else if (modelCtrlId == InternalAlgorithmCtrl::s_ModelCtrlId)
            {
                modelCtrl = new InternalAlgorithmCtrl();
                modelCtrl->Load(ar);
            }
            else
            {
            }

            if (modelCtrl != NULL)
            {
                m_ModelCtrlList.push_back(modelCtrl);
            }
            else
            {
                Utility::PromptErrorMessage(TEXT("读取模型文件失败."));
                return;
            }
        }

        UINT32 connectorListSize = 0;
        ar >> connectorListSize;

        for (UINT32 i = 0; i < connectorListSize; ++i)
        {
            Connector *connector = new Connector();
            connector->Load(ar, *this);

            m_ConnectorList.push_back(connector);
        }

        ar >> m_CurrentComponentId;
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

// Operations
bool CModelDoc::AddModelCtrl(ModelCtrl *modelCtrl)
{
    if (modelCtrl == NULL)
    {
        return false;
    }

    if (modelCtrl->SetId(m_CurrentComponentId))
    {
        ++m_CurrentComponentId;
    }

    m_ModelCtrlList.push_front(modelCtrl);
    return true;
}

bool CModelDoc::RemoveModelCtrl(ModelCtrl *modelCtrl)
{
    for (ModelCtrlList::iterator it = m_ModelCtrlList.begin();
        it != m_ModelCtrlList.end();
        ++it)
    {
        if ((*it) == modelCtrl)
        {
            m_ModelCtrlList.erase(it);
            return true;
        }
    }
    return false;
}

bool CModelDoc::AddConnector(Connector *connector)
{
    if (connector == NULL)
    {
        return false;
    }

    m_ConnectorList.push_front(connector);
    return true;
}
