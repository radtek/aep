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
    CLIENT_CIID_MOTION,
END_CLIENT_CIID

enum CLIENT_CCID
{
    CLIENT_CCID_AIRCRAFT,
    CLIENT_CCID_ULM,
    CLIENT_CCID_ALM,
};

interface IMotion : IComponent
{
    virtual void _stdcall Move(Vector &coordinate, double time) = 0;
};

interface IAircraft : IParam
{
    virtual void _stdcall Fly(double time) = 0;
};

interface INoise : IComponent
{
    virtual RC _stdcall Affect(Vector &data) = 0;
};

#endif // __CLIENT_INTERFACES_H__
