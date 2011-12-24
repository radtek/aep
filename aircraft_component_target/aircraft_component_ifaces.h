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
    CLIENT_CIID_MEASURE,
END_CLIENT_CIID

BEGIN_CLIENT_CCID
    CLIENT_CCID_AIRCRAFT,
    CLIENT_CCID_MISSILE,
    CLIENT_CCID_ULM,
    CLIENT_CCID_ALM,
    CLIENT_CCID_WHITE_NOISE,
    CLIENT_CCID_AIRCRAFT_TARGET_MEASURE,
END_CLIENT_CCID

interface IMotion : IComponent
{
    virtual void _stdcall Move(Vector &coordinate, double time) = 0;
};

interface IAircraft : IParam
{
    virtual void _stdcall Fly(double time) = 0;
};

interface ITarget : IParam
{
    virtual void _stdcall Fly(double time) = 0;
};

interface INoise : IComponent
{
    virtual double _stdcall Affect(double data) = 0;

    virtual double _stdcall GetMean() = 0;
    virtual double _stdcall GetVariance() = 0;
};

#endif // __CLIENT_INTERFACES_H__
