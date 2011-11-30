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

RC ULM::GetAttribute(UINT32 aid, void **attr)
{
    RC rc;
    return rc;
}

RC ULM::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;
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
