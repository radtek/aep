/**
* @file
* @brief ���������ӿ�ͷ�ļ�.
* @author ruoxi
*
* �����˷���������е�ȫ���ӿ�.
*/

#ifndef __CLIENT_INTERFACES_H__
#define __CLIENT_INTERFACES_H__

#include "interfaces.h"

BEGIN_CLIENT_CIID
    CLIENT_CIID_VECTOR,
    CLIENT_CIID_MOVEMENT,
    CLIENT_CIID_AIRCRAFT,
END_CLIENT_CIID

interface IVector : IComponent
{
    virtual double _stdcall GetX() = 0;
    virtual void _stdcall SetX(double x) = 0;

    virtual double _stdcall GetY() = 0;
    virtual void _stdcall SetY(double y) = 0;

    virtual double _stdcall GetZ() = 0;
    virtual void _stdcall SetZ(double z) = 0;
};

interface IMovement : IComponent
{
    virtual RC _stdcall Move(IVector **coordinate, IVector **speed, double second) = 0;
};

interface IAircraft : IComponent
{
    virtual RC _stdcall GetCoordinate(IVector **coordinate) = 0;
    virtual RC _stdcall SetCoordinate(IVector *coordinate) = 0;

    virtual RC _stdcall GetSpeed(IVector **speed) = 0;
    virtual RC _stdcall SetSpeed(IVector *speed) = 0;

    virtual RC _stdcall GetMovement(IMovement **movement) = 0;
    virtual RC _stdcall SetMovement(IMovement *movement) = 0;

    virtual RC _stdcall Fly(double second) = 0;
};

#endif // __CLIENT_INTERFACES_H__
