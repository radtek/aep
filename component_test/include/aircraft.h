/**
* @file
* @brief 飞行器类头文件.
* @author ruoxi
*
* 定义了飞行器类.
*/

#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "client_interfaces.h"

class Aircraft : public IAircraft
{
public:
    Aircraft();
    virtual ~Aircraft();

    virtual RC _stdcall QueryInterface(UINT32 iid, void **ppi);

    virtual Vector _stdcall GetStartCoordinate();
    virtual void _stdcall SetStartCoordinate(Vector coordinate);

    virtual Vector _stdcall GetStartVelocity();
    virtual void _stdcall SetStartVelocity(Vector velocity);

    virtual Vector _stdcall GetCurrentCoordinate();
    virtual void _stdcall SetCurrentCoordinate(Vector coordinate);

    virtual Vector _stdcall GetCurrentVelocity();
    virtual void _stdcall SetCurrentVelocity(Vector velocity);

    virtual IMotion *_stdcall GetMotion();
    virtual void _stdcall SetMotion(IMotion *motion);

    virtual void _stdcall Fly(double second);
private:
    Vector m_StartCoordinate;
    Vector m_CurrentCoordinate;

    Vector m_StartVelocity;
    Vector m_CurrentVelocity;

    IMotion *m_Motion;
};

extern Aircraft *CreateAircraft();

#endif // __AIRCRAFT_H__
