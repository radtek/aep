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
        IData *output1 = NULL, *output2 = NULL;
        RC rc1, rc2;
        rc1 = m_Component->GetOutput1(output1);
        rc2 = m_Component->GetOutput2(output2);
        if (OK != rc1 && OK != rc2)
        {
            return false;
        }
        if ((OK == rc1) && (OK == componentCtrl->m_Component->SetInput(output1)))
        {
            return true;
        }
        if ((OK == rc2) && (OK == componentCtrl->m_Component->SetInput(output2)))
        {
            return true;
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
