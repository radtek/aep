/**
* @file
* @brief 匀加速直线运动类头文件.
* @author ruoxi
*
* 定义了匀加速直线运动类.
*/

#ifndef __ACCELERATION_LINEAR_MOTION_H__
#define __ACCELERATION_LINEAR_MOTION_H__

#include "client_interfaces.h"

class AccelerationLinearMotion : public IMotion
{
public:
    AccelerationLinearMotion();
    virtual ~AccelerationLinearMotion();

    virtual RC _stdcall QueryInterface(UINT32 iid, void **ppi);

    virtual Vector _stdcall GetCurrentVelocity();
    virtual Vector _stdcall Move(Vector coordinate, double second);
private:
    Vector m_Velocity;
    Vector m_Acceleration;
};

extern AccelerationLinearMotion *CreateAccelerationLinearMotion();

#endif // __ACCELERATION_LINEAR_MOTION_H__
