#include "stdafx.h"
#include "model_app.h"

#include "attribute_bar.h"

#include "component_ctrl.h"

ComponentCtrl::ComponentCtrl(IComponent *component, CPoint position)
:
RectCtrl(position),
m_Component(component)
{
}

ComponentCtrl::~ComponentCtrl()
{
    m_Component->Destroy();
}

void ComponentCtrl::Save(CArchive &ar)
{
    ar << s_ModelCtrlId;

    RectCtrl::Save(ar);

    m_Component->Save(ar);
}

void ComponentCtrl::Load(CArchive &ar)
{
    RectCtrl::Load(ar);

    UINT32 componentId;
    ar >> componentId;

    m_Component = theApp.m_Platform.GetComponentTypeMap()[componentId].Factory();
    m_Component->Load(ar);
}

void ComponentCtrl::Export(CArchive &ar)
{
    m_Component->Save(ar);
}

bool ComponentCtrl::Connect(ModelCtrl *modelCtrl)
{
    ComponentCtrl *componentCtrl = dynamic_cast<ComponentCtrl *>(modelCtrl);
    if (NULL != componentCtrl)
    {
        // return m_Component->Connect(componentCtrl->m_Component);
        IData *output = NULL;
        if (OK != m_Component->GetOutput(output))
        {
            return false;
        }
        if (OK != componentCtrl->m_Component->SetInput(output))
        {
            return false;
        }
    }
    return false;
}

void ComponentCtrl::Config()
{
    ComponentType componentType = Platform::GetInstance().GetComponentTypeMap()[m_Component->GetTypeId()];
    AfxSetResourceHandle(componentType.DllHandle);
    m_Component->Config();
    AfxSetResourceHandle(AfxGetInstanceHandle());
}

IComponent *ComponentCtrl::GetComponent()
{
    return m_Component;
}

UINT32 ComponentCtrl::GetId()
{
    return m_Component->GetId();
}

bool ComponentCtrl::SetId(UINT32 id)
{
    m_Component->SetId(id);
    return true;
}

wstring ComponentCtrl::GetTitle()
{
    return m_Component->GetName();
}

void ComponentCtrl::UpdateAttributeBar()
{
    GetAttributeBar().SetComponent(m_Component);
}

void ComponentCtrl::ClearAttributeBar()
{
    GetAttributeBar().Clear();
}
