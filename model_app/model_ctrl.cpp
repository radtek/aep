#include "stdafx.h"
#include "model_app.h"
#include "main_frm.h"

#include "model_ctrl.h"

#include "connector.h"

ModelCtrl::ModelCtrl()
:
m_IsSelected(false)
{
}

ModelCtrl::~ModelCtrl()
{
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

void ModelCtrl::Config()
{
    return;
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
