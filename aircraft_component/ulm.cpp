/**
* @file
* @brief 飞行器类cpp文件.
* @author ruoxi
*
* 实现了飞行器类.
*/

#include "ulm.h"

ULM::ULM()
{
}

ULM::~ULM()
{
}

UINT32 ULM::GetTypeId()
{
    return s_ComponentId;
}

void ULM::Destroy()
{
    delete this;
}

void *ULM::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_MOTION == iid)
    {
        iface = static_cast<IMotion *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 ULM::GetId()
{
    return m_Id;
}

void ULM::SetId(UINT32 id)
{
    m_Id = id;
}

wstring ULM::GetName()
{
    return m_Name;
}

void ULM::SetName(wstring name)
{
    m_Name = name;
}

void ULM::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = ULMAID_V_X;
    attribute.Name = TEXT("初始速度X");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);

    attribute.Id = ULMAID_V_Y;
    attribute.Name = TEXT("初始速度Y");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);

    attribute.Id = ULMAID_V_Z;
    attribute.Name = TEXT("初始速度Z");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);
}

RC ULM::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case ULMAID_V_X:
        *((double *)attr) = m_Velocity.x;
        break;
    case ULMAID_V_Y:
        *((double *)attr) = m_Velocity.y;
        break;
    case ULMAID_V_Z:
        *((double *)attr) = m_Velocity.z;
        break;
    }

    return rc;
}

RC ULM::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case ULMAID_V_X:
        m_Velocity.x = *((double *)attr);
        break;
    case ULMAID_V_Y:
        m_Velocity.y = *((double *)attr);
        break;
    case ULMAID_V_Z:
        m_Velocity.z = *((double *)attr);
        break;
    }

    return rc;
}

bool ULM::Connect(IComponent *component)
{
    return false;
}

void ULM::Move(Vector &coordinate, double time)
{
    coordinate += (m_Velocity * time);
}

ULM *ULM::Factory()
{
    ULM *ulm = new ULM;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    ulm->m_Name = name;
    ++s_Count;
    delete[] name;
    return ulm;
}

LPCWSTR ULM::s_ComponentName = TEXT("匀速直线运动");

UINT32 ULM::s_Count = 0;
