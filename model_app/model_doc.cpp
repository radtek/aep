// model_doc.cpp : implementation of the CModelDoc class
//

#include "stdafx.h"
#include "model_app.h"

#include "model_doc.h"
#include "model_view.h"

#include "main_frm.h"

#include "component_ctrl.h"
#include "internal_algorithm_ctrl.h"
#include "connector_ctrl.h"

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
m_CurrentState(STATE_NORMAL),
m_CurrentComponentTypeId(-1),
m_CurrentModelCtrl(NULL),
m_CurrentInternalAlgorithmId(-1),
m_CurrentConnectorId(-1),
m_CurrentConnectorCtrl(NULL),
m_Moved(false),
m_CurrentComponentId(theApp.m_Platform.GetComponentIdStart())
{
	// TODO: add one-time construction code here

}

CModelDoc::~CModelDoc()
{
    DeleteContents();
}

BOOL CModelDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

void CModelDoc::DeleteContents()
{
    m_CurrentState = STATE_NORMAL;
    UnSelectAll();
    m_ModelCtrlList.clear();
    m_ConnectorCtrlList.clear();
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

        ar << m_ConnectorCtrlList.size();

        for (ConnectorCtrlList::iterator it = m_ConnectorCtrlList.begin();
            it != m_ConnectorCtrlList.end(); ++it)
        {
            ConnectorCtrl *connectorCtrl = (*it);
            connectorCtrl->Save(ar);
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

        UINT32 connectorCtrlListSize = 0;
        ar >> connectorCtrlListSize;

        for (UINT32 i = 0; i < connectorCtrlListSize; ++i)
        {
            ConnectorCtrl *connectorCtrl = new ConnectorCtrl();
            connectorCtrl->Load(ar, *this);

            m_ConnectorCtrlList.push_back(connectorCtrl);
        }

        ar >> m_CurrentComponentId;
	}
}

RC CModelDoc::ExportModel(CArchive &ar)
{
    RC rc;

    ar << m_ModelCtrlList.size();

    for (ModelCtrlList::iterator it = m_ModelCtrlList.begin();
        it != m_ModelCtrlList.end(); ++it)
    {
        ModelCtrl *modelCtrl = (*it);
        modelCtrl->Export(ar);
    }

    ar << m_ConnectorCtrlList.size();

    for (ConnectorCtrlList::iterator it = m_ConnectorCtrlList.begin();
        it != m_ConnectorCtrlList.end(); ++it)
    {
        ConnectorCtrl *connectorCtrl = (*it);
        connectorCtrl->Export(ar);
    }

    return rc;
}

Model CModelDoc::ExportModel()
{
    ComponentList componentList;
    for (ModelCtrlList::iterator it = m_ModelCtrlList.begin();
        it != m_ModelCtrlList.end(); ++it)
    {
        ComponentCtrl *componentCtrl = dynamic_cast<ComponentCtrl *>(*it);
        if (componentCtrl != NULL)
        {
            componentList.push_back(componentCtrl->GetComponent());
        }
    }

    ConnectorList connectorList;
    for (ConnectorCtrlList::iterator it = m_ConnectorCtrlList.begin();
        it != m_ConnectorCtrlList.end(); ++it)
    {
        ConnectorCtrl *connectorCtrl = (*it);
        ModelCtrl *source = connectorCtrl->GetSource();
        ModelCtrl *target = connectorCtrl->GetTarget();
        if (source != NULL && target != NULL)
        {
            Connector connector;
            ComponentCtrl *componentCtrl = dynamic_cast<ComponentCtrl *>(source);
            if (componentCtrl != NULL)
            {
                connector.Source = componentCtrl->GetComponent();
            }
            componentCtrl = dynamic_cast<ComponentCtrl *>(target);
            if (componentCtrl != NULL)
            {
                connector.Target = componentCtrl->GetComponent();
            }
            if (connector.Source != NULL && connector.Target != NULL)
            {
                connectorList.push_back(connector);
            }
        }
    }

    return Model(componentList, connectorList);
}

RC CModelDoc::DrawData()
{
    RC rc;

    if (!theApp.m_Engine)
    {
        return RC::MODEL_MATLAB_ENGINE_ERROR;
    }

    for (ConnectorCtrlList::iterator it = m_ConnectorCtrlList.begin();
        it != m_ConnectorCtrlList.end(); ++it)
    {
        ConnectorCtrl *connectorCtrl = (*it);
//        if (!connectorCtrl->Connect())
//        {
//            return RC::MODEL_CONNECT_COMPONENT_ERROR;
//        }
    }

    bool hasParam = false;
    for (ModelCtrlList::iterator it = m_ModelCtrlList.begin();
        it != m_ModelCtrlList.end(); ++it)
    {
        ComponentCtrl *componentCtrl = dynamic_cast<ComponentCtrl *>(*it);
        if (!componentCtrl)
        {
            continue;
        }
        IComponent *component = componentCtrl->GetComponent();
        if (!component)
        {
            continue;
        }
        IParam *param = (IParam *)(component->GetInterface(CIID_IPARAM));
        if (!param)
        {
            continue;
        }
        hasParam = true;
        CHECK_RC(param->DrawFigure(theApp.m_Engine));
    }

    if (!hasParam)
    {
        return RC::MODEL_NO_PARAM_ERROR;
    }

    return rc;
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

void CModelDoc::SelectModelCtrl(ModelCtrl *modelCtrl)
{
    m_CurrentModelCtrl = modelCtrl;
    m_CurrentModelCtrl->Select();
}

void CModelDoc::SelectConnectorCtrl(ConnectorCtrl *connectorCtrl, CPoint point)
{
    m_CurrentConnectorCtrl = connectorCtrl;
    m_CurrentConnectorCtrl->Select(m_CurrentConnectorCtrl->HitTest(point));
}

void CModelDoc::UnSelectCurrentModelCtrl()
{
    m_CurrentModelCtrl->UnSelect();
    m_CurrentModelCtrl = NULL;
}

void CModelDoc::UnSelectCurrentConnectorCtrl()
{
    m_CurrentConnectorCtrl->Select(ConnectorCtrl::CSM_NONE);
    m_CurrentConnectorCtrl = NULL;
}

void CModelDoc::UnSelectAll()
{
    m_CurrentComponentTypeId = -1;
    if (m_CurrentModelCtrl != NULL)
    {
        m_CurrentModelCtrl->UnSelect();
        m_CurrentModelCtrl = NULL;
    }

    m_CurrentConnectorId = -1;
    if (m_CurrentConnectorCtrl != NULL)
    {
        m_CurrentConnectorCtrl->Select(ConnectorCtrl::CSM_NONE);
    }
}

void CModelDoc::RemoveCurrentModelCtrl()
{
    m_CurrentModelCtrl->UnSelect();
    m_CurrentModelCtrl->RemoveAllConnectorCtrl();
    for (ModelCtrlList::iterator it = m_ModelCtrlList.begin();
        it != m_ModelCtrlList.end(); ++it)
    {
        if (m_CurrentModelCtrl == (*it))
        {
            m_ModelCtrlList.erase(it);
            break;
        }
    }
    m_CurrentModelCtrl = NULL;
}

void CModelDoc::RemoveCurrentConnectorCtrl()
{
    m_CurrentConnectorCtrl->Select(ConnectorCtrl::CSM_NONE);
    m_CurrentConnectorCtrl->DisconnectAll();
    for (ConnectorCtrlList::iterator it = m_ConnectorCtrlList.begin();
        it != m_ConnectorCtrlList.end(); ++it)
    {
        if (m_CurrentConnectorCtrl == (*it))
        {
            m_ConnectorCtrlList.erase(it);
            break;
        }
    }
    m_CurrentConnectorCtrl = NULL;
}

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
    if (modelCtrl == NULL)
    {
        return false;
    }

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

bool CModelDoc::AddConnectorCtrl(ConnectorCtrl *connectorCtrl)
{
    if (connectorCtrl == NULL)
    {
        return false;
    }

    m_ConnectorCtrlList.push_front(connectorCtrl);
    return true;
}

bool CModelDoc::RemoveConnectorCtrl(ConnectorCtrl *connectorCtrl)
{
    if (connectorCtrl == NULL)
    {
        return false;
    }

    for (ConnectorCtrlList::iterator it = m_ConnectorCtrlList.begin();
        it != m_ConnectorCtrlList.end();
        ++it)
    {
        if ((*it) == connectorCtrl)
        {
            m_ConnectorCtrlList.erase(it);
            return true;
        }
    }
}
