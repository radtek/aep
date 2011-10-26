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

RC Aircraft::GetInterface(UINT32 iid, void **iface)
{
    if (CIID_ICOMPONENT == iid)
    {
        *iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_AIRCRAFT == iid)
    {
        *iface = static_cast<IAircraft *>(this);
    }
    else
    {
        *iface = 0;
        return RC::COMPONENT_GETINTERFACE_ERROR;
    }
    return OK;
}

RC Aircraft::GetAttribute(UINT32 aid, void **attr)
{
    if (ATTR_START_COORDINATE == aid)
    {
        *attr = m_StartCoordinate;
    }
    else if (ATTR_START_VELOCITY == aid)
    {
        *attr = m_StartVelocity;
    }
    else if (ATTR_CURRENT_COORDINATE == aid)
    {
        *attr = m_CurrentCoordinate;
    }
    else if (ATTR_CURRENT_VELOCITY == aid)
    {
        *attr = m_CurrentVelocity;
    }
    else if (ATTR_MOTION == aid)
    {
        *attr = m_Motion;
    }
    else
    {
        *attr = 0;
        return RC::COMPONENT_GETATTRIBUTE_ERROR;
    }
    return OK;
}

RC Aircraft::SetAttribute(UINT32 aid, void *attr)
{
    if (ATTR_START_COORDINATE == aid)
    {
        m_StartCoordinate = static_cast<Vector *>(attr);
    }
    else if (ATTR_START_VELOCITY == aid)
    {
        m_StartVelocity = static_cast<Vector *>(attr);
    }
    else if (ATTR_CURRENT_COORDINATE == aid)
    {
        m_CurrentCoordinate = static_cast<Vector *>(attr);
    }
    else if (ATTR_CURRENT_VELOCITY == aid)
    {
        m_CurrentVelocity = static_cast<Vector *>(attr);
    }
    else if (ATTR_MOTION == aid)
    {
        m_Motion = static_cast<IMotion *>(attr);
    }
    else
    {
        return RC::COMPONENT_SETATTRIBUTE_ERROR;
    }
    return OK;
}

RC Aircraft::Fly(double second)
{
    RC rc;
    CHECK_RC(m_Motion->GetCurrentVelocity(*m_CurrentVelocity));
    CHECK_RC(m_Motion->Move(*m_CurrentCoordinate, second));
    return rc;
}

const char *AircraftTypeName = "Acceleration linear motion";

UINT32 AircraftAttributeList[] =
{
    #undef DEFINE_ATTR
    /** @brief 重定义飞行器属性的外包宏DEFINE_ATTR. */
    #define DEFINE_ATTR(a, msg) Aircraft::a,
    /** @brief 用来开启允许包含aircraft_attrs.h头文件的开关. */
    #define __USE_AIRCRAFT_ATTRS__
    #include "aircraft_attrs.h"
};

Aircraft *AircraftFactory()
{
    return new Aircraft();
}
