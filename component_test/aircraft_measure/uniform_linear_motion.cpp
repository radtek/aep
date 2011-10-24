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

RC UniformLinearMotion::QueryInterface(UINT32 iid, void **ppi)
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

Vector UniformLinearMotion::GetCurrentVelocity()
{
    return m_Velocity;
}

Vector UniformLinearMotion::Move(Vector coordinate, double second)
{
    coordinate += (m_Velocity * second);

    return coordinate;
}

UniformLinearMotion *CreateUniformLinearMotion()
{
    return new UniformLinearMotion();
}
