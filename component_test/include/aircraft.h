/**
* @file
* @brief 飞行器类头文件.
* @author ruoxi
*
* 定义了飞行器类.
*/

#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "aircraft_measure_ifaces.h"

class Aircraft : public IAircraft
{
public:
    enum
    {
        #undef DEFINE_ATTR
        /** @brief 重定义飞行器属性的外包宏DEFINE_ATTR. */
        #define DEFINE_ATTR(a, msg) a,
        /** @brief 用来开启允许包含aircraft_attrs.h头文件的开关. */
        #define __USE_AIRCRAFT_ATTRS__
        #include "aircraft_attrs.h"
    };

public:
    Aircraft();
    virtual ~Aircraft();

    virtual RC _stdcall GetInterface(UINT32 iid, void **iface);
    virtual RC _stdcall Config(ComponentList *list);
    virtual RC _stdcall Destroy();
    virtual RC _stdcall GetName(LPWSTR *name);
    virtual RC _stdcall GetAttribute(UINT32 aid, void **attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);

    virtual RC _stdcall Fly(double time);

private:
    Vector *m_StartCoordinate;
    Vector *m_StartVelocity;

    Vector *m_CurrentCoordinate;
    Vector *m_CurrentVelocity;

    IMotion *m_Motion;

    LPWSTR m_Name;

    friend Aircraft *AircraftFactory();
};

extern LPCWSTR AircraftTypeName;

extern UINT32 AircraftAttributeList[];

extern UINT32 AircraftCount;

extern Aircraft *AircraftFactory();

extern void AircraftDestroy(Aircraft *aircraft);

#endif // __AIRCRAFT_H__
