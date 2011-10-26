/**
* @file
* @brief 匀速直线运动类cpp文件.
* @author ruoxi
*
* 实现了匀速直线运动类.
*/

#include "uniform_linear_motion.h"

UniformLinearMotion::UniformLinearMotion()
{
}

UniformLinearMotion::~UniformLinearMotion()
{
}

RC UniformLinearMotion::GetInterface(UINT32 iid, void **iface)
{
    if (CIID_ICOMPONENT == iid)
    {
        *iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_MOTION == iid)
    {
        *iface = static_cast<IMotion *>(this);
    }
    else
    {
        *iface = 0;
        return RC::COMPONENT_GETINTERFACE_ERROR;
    }
    return OK;
}

RC UniformLinearMotion::GetAttribute(UINT32 aid, void **attr)
{
    if (ATTR_VELOCITY == aid)
    {
        *attr = m_Velocity;
    }
    else if (ATTR_ACCELERATION == aid)
    {
        *attr = new Vector;
    }
    else
    {
        *attr = 0;
        return RC::COMPONENT_SETATTRIBUTE_ERROR;
    }
    return OK;
}

RC UniformLinearMotion::SetAttribute(UINT32 aid, void *attr)
{
    if (ATTR_VELOCITY == aid)
    {
        m_Velocity = static_cast<Vector *>(attr);
    }
    else if (ATTR_ACCELERATION == aid)
    {
    }
    else
    {
        return RC::COMPONENT_SETATTRIBUTE_ERROR;
    }
    return OK;
}

RC UniformLinearMotion::GetCurrentVelocity(Vector &velocity)
{
    velocity = (*m_Velocity);
    return OK;
}

RC UniformLinearMotion::Move(Vector &coordinate, double time)
{
    coordinate += ((*m_Velocity) * time);
    return OK;
}

LPCWSTR UniformLinearMotionTypeName = TEXT("Uniform linear motion");

UINT32 UniformLinearMotionAttributeList[] =
{
    #undef DEFINE_ATTR
    /** @brief 重定义匀速直线运动属性的外包宏DEFINE_ATTR. */
    #define DEFINE_ATTR(a, msg) UniformLinearMotion::a,
    /** @brief 用来开启允许包含uniform_linear_motion_attrs.h头文件的开关. */
    #define __USE_UNIFORM_LINEAR_MOTION_ATTRS__
    #include "uniform_linear_motion_attrs.h"
};

UniformLinearMotion *UniformLinearMotionFactory()
{
    return new UniformLinearMotion();
}
