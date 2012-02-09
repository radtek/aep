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
    CLIENT_CIID_AIRCRAFT,
    CLIENT_CIID_TARGET,
    CLIENT_CIID_MOTION,
    CLIENT_CIID_NOISE,
    CLIENT_CIID_REAL_VALUE,
END_CLIENT_CIID

BEGIN_CLIENT_CCID
    CLIENT_CCID_AIRCRAFT,
    CLIENT_CCID_MISSILE,
    CLIENT_CCID_ULM,
    CLIENT_CCID_ALM,
    CLIENT_CCID_WHITE_NOISE,
    CLIENT_CCID_ATD,
END_CLIENT_CCID

struct IMotion : IComponent
{
    virtual void _stdcall Move(Vector &coordinate, double time) = 0;
};

struct IAircraft : IComponent
{
    virtual void _stdcall Fly(double time) = 0;
    virtual Vector _stdcall GetCurrentCoordinate() = 0;
};

struct ITarget : IComponent
{
    virtual void _stdcall Fly(double time) = 0;
    virtual Vector _stdcall GetCurrentCoordinate() = 0;
};

struct INoise : IComponent
{
    virtual double _stdcall Affect(double data) = 0;

    virtual double _stdcall GetMean() = 0;
    virtual double _stdcall GetVariance() = 0;
};

struct IRealValue : IParam
{
};

#endif // __CLIENT_INTERFACES_H__
