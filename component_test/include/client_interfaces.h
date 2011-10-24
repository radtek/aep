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
    virtual Vector _stdcall GetCurrentVelocity() = 0;
    virtual Vector _stdcall Move(Vector coordinate, double second) = 0;
};

interface IAircraft : IComponent
{
    virtual Vector _stdcall GetStartCoordinate() = 0;
    virtual void _stdcall SetStartCoordinate(Vector coordinate) = 0;

    virtual Vector _stdcall GetStartVelocity() = 0;
    virtual void _stdcall SetStartVelocity(Vector velocity) = 0;

    virtual Vector _stdcall GetCurrentCoordinate() = 0;
    virtual void _stdcall SetCurrentCoordinate(Vector coordinate) = 0;

    virtual Vector _stdcall GetCurrentVelocity() = 0;
    virtual void _stdcall SetCurrentVelocity(Vector velocity) = 0;

    virtual IMotion *_stdcall GetMotion() = 0;
    virtual void _stdcall SetMotion(IMotion *Motion) = 0;

    virtual void _stdcall Fly(double second) = 0;
};

#endif // __CLIENT_INTERFACES_H__
