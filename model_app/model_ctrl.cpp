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
    UpdateOutputBar();
}

void ModelCtrl::UnSelect()
{
    m_IsSelected = false;
    ClearOutputBar();
}

COutputBar &ModelCtrl::GetOutputBar()
{
    CMainFrame *mainFrame = DYNAMIC_DOWNCAST(CMainFrame, theApp.m_pMainWnd);
    return mainFrame->GetOutputBar();
}
