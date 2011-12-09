#include "stdafx.h"
#include "model_app.h"
#include "main_frm.h"

#include "model_ctrl.h"

#include "connector.h"

UINT32 ModelCtrl::s_IdCount = 0;

ModelCtrl::ModelCtrl()
:
m_IsSelected(false)
{
    m_Id = s_IdCount++;
}

ModelCtrl::~ModelCtrl()
{
}

void ModelCtrl::Save(CArchive &ar)
{
    ar << m_Id;
}

void ModelCtrl::Load(CArchive &ar)
{
    ar >> m_Id;
    if (s_IdCount <= m_Id)
    {
        s_IdCount = m_Id + 1;
    }
}

UINT32 ModelCtrl::GetId()
{
    return m_Id;
}

void ModelCtrl::Select()
{
    m_IsSelected = true;
    UpdateAttributeBar();
}

void ModelCtrl::UnSelect()
{
    m_IsSelected = false;
    ClearAttributeBar();
}

void ModelCtrl::AddConnector(Connector *connector)
{
    m_ConnectorList.push_back(connector);
}

void ModelCtrl::RemoveConnector(Connector *connector)
{
    for (list<Connector *>::iterator it = m_ConnectorList.begin();
        it != m_ConnectorList.end(); ++it)
    {
        if ((*it) == connector)
        {
            m_ConnectorList.erase(it);
            return;
        }
    }
}

CAttributeBar &ModelCtrl::GetAttributeBar()
{
    CMainFrame *mainFrame = DYNAMIC_DOWNCAST(CMainFrame, theApp.m_pMainWnd);
    return mainFrame->GetAttributeBar();
}
