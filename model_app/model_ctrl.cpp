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

CAttributeBar &ModelCtrl::GetAttributeBar()
{
    CMainFrame *mainFrame = DYNAMIC_DOWNCAST(CMainFrame, theApp.m_pMainWnd);
    return mainFrame->GetAttributeBar();
}
