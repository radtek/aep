/**
* @file
* @brief 飞行器类cpp文件.
* @author ruoxi
*
* 实现了飞行器类.
*/

#include "aircraft.h"

Aircraft::Aircraft()
{
}

Aircraft::~Aircraft()
{
}

RC Aircraft::QueryInterface(UINT32 iid, void **ppi)
{
    if (CIID_ICOMPONENT == iid)
    {
        *ppi = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_AIRCRAFT == iid)
    {
        *ppi = static_cast<IAircraft *>(this);
    }
    else
    {
        *ppi = 0;
        return RC::COMPONENT_QUERYINTERFACE_ERROR;
    }
    return OK;
}

Vector Aircraft::GetStartCoordinate()
{
    return m_StartCoordinate;
}

void Aircraft::SetStartCoordinate(Vector coordinate)
{
    m_StartCoordinate = coordinate;
}

Vector Aircraft::GetStartVelocity()
{
    return m_StartVelocity;
}

void Aircraft::SetStartVelocity(Vector speed)
{
    m_StartVelocity = speed;
}

Vector Aircraft::GetCurrentCoordinate()
{
    return m_CurrentCoordinate;
}

void Aircraft::SetCurrentCoordinate(Vector coordinate)
{
    coordinate = m_CurrentCoordinate;
}

Vector Aircraft::GetCurrentVelocity()
{
    return m_CurrentVelocity;
}

void Aircraft::SetCurrentVelocity(Vector speed)
{
    m_CurrentVelocity = speed;
}

IMotion *Aircraft::GetMotion()
{
    return m_Motion;
}

void Aircraft::SetMotion(IMotion *motion)
{
    m_Motion = motion;
}

void Aircraft::Fly(double second)
{
    m_CurrentVelocity = m_Motion->GetCurrentVelocity();
    m_CurrentCoordinate = m_Motion->Move(m_CurrentCoordinate, second);
}

Aircraft *CreateAircraft()
{
    return new Aircraft();
}
