/**
* @file
* @brief 飞行器测距接口头文件.
* @author ruoxi
*
* 定义了飞行器测距中的全部接口.
*/

#ifndef __CLIENT_INTERFACES_H__
#define __CLIENT_INTERFACES_H__

#include "interfaces.h"
#include "vector.h"

BEGIN_CLIENT_CIID
    CLIENT_CIID_MOTION,
    CLIENT_CIID_AIRCRAFT,
END_CLIENT_CIID

interface IMotion : IComponent
{
    virtual RC _stdcall GetCurrentVelocity(Vector &velocity) = 0;
    virtual RC _stdcall Move(Vector &coordinate, double time) = 0;
};

interface IAircraft : IComponent
{
    virtual RC _stdcall Fly(double time) = 0;
};

#endif // __CLIENT_INTERFACES_H__
