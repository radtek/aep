/**
* @file
* @brief �ȼ���ֱ���˶���cpp�ļ�.
* @author ruoxi
*
* ʵ�����ȼ���ֱ���˶���.
*/

#include "acceleration_linear_motion.h"
#include "utility.h"

AccelerationLinearMotion::AccelerationLinearMotion()
{
}

AccelerationLinearMotion::~AccelerationLinearMotion()
{
}

RC AccelerationLinearMotion::GetInterface(UINT32 iid, void **iface)
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

RC AccelerationLinearMotion::Config(ComponentList *list)
{
    Utility::PromptLastErrorMessage();
    return OK;
}

RC AccelerationLinearMotion::Destroy()
{
    delete this;
    return OK;
}

RC AccelerationLinearMotion::GetName(LPWSTR *name)
{
    *name = m_Name;
    return OK;
}

RC AccelerationLinearMotion::GetAttribute(UINT32 aid, void **attr)
{
    if (ATTR_NAME == aid)
    {
        *attr = m_Name;
    }
    else if (ATTR_VELOCITY == aid)
    {
        *attr = m_Velocity;
    }
    else if (ATTR_ACCELERATION == aid)
    {
        *attr = m_Acceleration;
    }
    else
    {
        *attr = 0;
        return RC::COMPONENT_GETATTRIBUTE_ERROR;
    }
    return OK;
}

RC AccelerationLinearMotion::SetAttribute(UINT32 aid, void *attr)
{
    if (ATTR_NAME == aid)
    {
        m_Name = (LPWSTR)attr;
    }
    else if (ATTR_VELOCITY == aid)
    {
        m_Velocity = static_cast<Vector *>(attr);
    }
    else if (ATTR_ACCELERATION == aid)
    {
        m_Acceleration = static_cast<Vector *>(attr);
    }
    else
    {
        return RC::COMPONENT_SETATTRIBUTE_ERROR;
    }
    return OK;
}

RC AccelerationLinearMotion::GetCurrentVelocity(Vector &velocity)
{
    velocity = (*m_Velocity);
    return OK;
}

RC AccelerationLinearMotion::Move(Vector &coordinate, double time)
{
    coordinate += ((*m_Velocity) * time + (*m_Acceleration) * time * time * 0.5);
    (*m_Velocity) += ((*m_Acceleration) * time);
    return OK;
}

LPCWSTR AccelerationLinearMotionTypeName = TEXT("Acceleration linear motion");

UINT32 AccelerationLinearMotionAttributeList[] =
{
    #undef DEFINE_ATTR
    /** @brief �ض����ȼ���ֱ���˶����Ե������DEFINE_ATTR. */
    #define DEFINE_ATTR(a, msg) AccelerationLinearMotion::a,
    /** @brief ���������������acceleration_linear_motion_attrs.hͷ�ļ��Ŀ���. */
    #define __USE_ACCELERATION_LINEAR_MOTION_ATTRS__
    #include "acceleration_linear_motion_attrs.h"
};

UINT32 AccelerationLinearMotionCount = 0;

AccelerationLinearMotion *AccelerationLinearMotionFactory()
{
    AccelerationLinearMotion *accelerationLinearMotion = new AccelerationLinearMotion();
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s %u"), AccelerationLinearMotionTypeName, AccelerationLinearMotionCount);
    accelerationLinearMotion->m_Name = name;
    ++AccelerationLinearMotionCount;
    return accelerationLinearMotion;
}

void AccelerationLinearMotionDestroy(AccelerationLinearMotion *accelerationLinearMotion)
{
    delete accelerationLinearMotion;
}
