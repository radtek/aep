#include "stdafx.h"
#include "model_app.h"
#include "main_frm.h"

#include "model_ctrl.h"

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

void ModelCtrl::AddConnectorCtrl(ConnectorCtrl *connectorCtrl)
{
    m_ConnectorCtrlList.push_back(connectorCtrl);
}

void ModelCtrl::RemoveConnectorCtrl(ConnectorCtrl *connectorCtrl)
{
    for (list<ConnectorCtrl *>::iterator it = m_ConnectorCtrlList.begin();
        it != m_ConnectorCtrlList.end(); ++it)
    {
        if ((*it) == connectorCtrl)
        {
            m_ConnectorCtrlList.erase(it);
            return;
        }
    }
}

CAttributeBar &ModelCtrl::GetAttributeBar()
{
    CMainFrame *mainFrame = DYNAMIC_DOWNCAST(CMainFrame, theApp.m_pMainWnd);
    return mainFrame->GetAttributeBar();
}
