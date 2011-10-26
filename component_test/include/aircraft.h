/**
* @file
* @brief ��������ͷ�ļ�.
* @author ruoxi
*
* �����˷�������.
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
        /** @brief �ض�����������Ե������DEFINE_ATTR. */
        #define DEFINE_ATTR(a, msg) a,
        /** @brief ���������������aircraft_attrs.hͷ�ļ��Ŀ���. */
        #define __USE_AIRCRAFT_ATTRS__
        #include "aircraft_attrs.h"
    };

public:
    Aircraft();
    virtual ~Aircraft();

    virtual RC _stdcall GetInterface(UINT32 iid, void **iface);
    virtual RC _stdcall GetAttribute(UINT32 aid, void **attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);

    virtual RC _stdcall Fly(double time);

private:
    Vector *m_StartCoordinate;
    Vector *m_StartVelocity;

    Vector *m_CurrentCoordinate;
    Vector *m_CurrentVelocity;

    IMotion *m_Motion;
};

extern const char *AircraftTypeName;

extern UINT32 AircraftAttributeList[];

extern Aircraft *AircraftFactory();

#endif // __AIRCRAFT_H__
