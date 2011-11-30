/**
* @file
* @brief 飞行器类cpp文件.
* @author ruoxi
*
* 实现了飞行器类.
*/

#include "alm.h"

ALM::ALM()
{
}

ALM::~ALM()
{
}

void ALM::Destroy()
{
    delete this;
}

void *ALM::GetInterface(UINT32 iid)
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

UINT32 ALM::GetId()
{
    return m_Id;
}

void ALM::SetId(UINT32 id)
{
    m_Id = id;
}

wstring ALM::GetName()
{
    return m_Name;
}

void ALM::SetName(wstring name)
{
    m_Name = name;
}

RC ALM::GetAttribute(UINT32 aid, void **attr)
{
    RC rc;
    return rc;
}

RC ALM::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;
    return rc;
}

bool ALM::Connect(IComponent *component)
{
    return false;
}

void ALM::Move(Vector &coordinate, double time)
{
    coordinate += (m_Velocity * time + m_Acceleration * time * time * 0.5);
    m_Velocity += (m_Acceleration * time);
}

ALM *ALM::Factory()
{
    ALM *alm = new ALM;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    alm->m_Name = name;
    ++s_Count;
    delete[] name;
    return alm;
}

LPCWSTR ALM::s_ComponentName = TEXT("匀加速直线运动");

UINT32 ALM::s_Count = 0;
