/**
* @file
* @brief ����ֱ���˶���ͷ�ļ�.
* @author ruoxi
*
* ����������ֱ���˶���.
*/

#ifndef __UNIFORM_LINEAR_MOTION_H__
#define __UNIFORM_LINEAR_MOTION_H__

#include "client_interfaces.h"

class UniformLinearMotion : public IMotion
{
public:
    UniformLinearMotion();
    virtual ~UniformLinearMotion();

    virtual RC _stdcall QueryInterface(UINT32 iid, void **ppi);

    virtual Vector _stdcall GetCurrentVelocity();
    virtual Vector _stdcall Move(Vector coordinate, double second);
private:
    Vector m_Velocity;
};

extern UniformLinearMotion *CreateUniformLinearMotion();

#endif // __UNIFORM_LINEAR_MOTION_H__
