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

bool ComponentCtrl::SetId(UINT32 id)
{
    m_Component->SetId(id);
    return true;
}

wstring ComponentCtrl::GetTitle()
{
    return m_Component->GetName();
}

void ComponentCtrl::UpdateOutputBar()
{
    GetOutputBar().SetComponent(m_Component);
}

void ComponentCtrl::ClearOutputBar()
{
    GetOutputBar().Clear();
}
