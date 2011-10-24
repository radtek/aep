/**
* @file
* @brief 匀加速直线运动类cpp文件.
* @author ruoxi
*
* 实现了匀加速直线运动类.
*/

#include "acceleration_linear_motion.h"

AccelerationLinearMotion::AccelerationLinearMotion()
{
}

AccelerationLinearMotion::~AccelerationLinearMotion()
{
}

RC AccelerationLinearMotion::QueryInterface(UINT32 iid, void **ppi)
{
    if (CIID_ICOMPONENT == iid)
    {
        *ppi = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_MOTION == iid)
    {
        *ppi = static_cast<IMotion *>(this);
    }
    else
    {
        *ppi = 0;
        return RC::COMPONENT_QUERYINTERFACE_ERROR;
    }
    return OK;
}

Vector AccelerationLinearMotion::GetCurrentVelocity()
{
    return m_Velocity;
}

Vector AccelerationLinearMotion::Move(Vector coordinate, double second)
{
    coordinate += (m_Velocity * second + m_Acceleration * second * second * 0.5);
    m_Velocity += (m_Acceleration * second);

    return coordinate;
}

AccelerationLinearMotion *CreateAccelerationLinearMotion()
{
    return new AccelerationLinearMotion();
}
