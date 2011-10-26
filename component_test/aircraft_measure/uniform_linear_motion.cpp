/**
* @file
* @brief ����ֱ���˶���cpp�ļ�.
* @author ruoxi
*
* ʵ��������ֱ���˶���.
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
    /** @brief �ض�������ֱ���˶����Ե������DEFINE_ATTR. */
    #define DEFINE_ATTR(a, msg) UniformLinearMotion::a,
    /** @brief ���������������uniform_linear_motion_attrs.hͷ�ļ��Ŀ���. */
    #define __USE_UNIFORM_LINEAR_MOTION_ATTRS__
    #include "uniform_linear_motion_attrs.h"
};

UniformLinearMotion *UniformLinearMotionFactory()
{
    return new UniformLinearMotion();
}
