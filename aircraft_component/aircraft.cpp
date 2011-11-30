/**
* @file
* @brief 飞行器类cpp文件.
* @author ruoxi
*
* 实现了飞行器类.
*/

#include "aircraft.h"

Aircraft::Aircraft()
:
m_Motion(NULL)
{
}

Aircraft::~Aircraft()
{
}

void Aircraft::Destroy()
{
    delete this;
}

void *Aircraft::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CIID_IPARAM == iid)
    {
        iface = static_cast<IParam *>(this);
    }
    else if (CLIENT_CIID_AIRCRAFT == iid)
    {
        iface = static_cast<IAircraft *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 Aircraft::GetId()
{
    return m_Id;
}

void Aircraft::SetId(UINT32 id)
{
    m_Id = id;
}

wstring Aircraft::GetName()
{
    return m_Name;
}

void Aircraft::SetName(wstring name)
{
    m_Name = name;
}

RC Aircraft::GetAttribute(UINT32 aid, void **attr)
{
    RC rc;
    return rc;
}

RC Aircraft::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;
    return rc;
}

bool Aircraft::Connect(IComponent *component)
{
    IMotion *motion = (IMotion *)component->GetInterface(CLIENT_CIID_MOTION);
    if (NULL != motion)
    {
        m_Motion = motion;
        return true;
    }
    return false;
}

Param *Aircraft::ToParam()
{
    Param *param = mxCreateDoubleMatrix(1, 9, mxREAL);
    /*
    double *data = mxGetPr(param);
    data[0] = m_CurrentCoordinate.x;
    data[1] = m_CurrentCoordinate.y;
    data[2] = m_CurrentCoordinate.z;
    data[3] = m_CurrentVelocity.x;
    data[4] = m_CurrentVelocity.y;
    data[5] = m_CurrentVelocity.z;
    data[6] = 0;
    data[7] = 0;
    data[8] = 0;
    */
    return param;
}

UINT32 Aircraft::GetParamSize()
{
    return 9;
}

void Aircraft::Fly(double time)
{
    m_Motion->Move(m_Coordinate, time);
}

Aircraft *Aircraft::Factory()
{
    Aircraft *aircraft = new Aircraft;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    aircraft->m_Name = name;
    ++s_Count;
    delete[] name;
    return aircraft;
}

LPCWSTR Aircraft::s_ComponentName = TEXT("飞行器");

UINT32 Aircraft::s_Count = 0;
