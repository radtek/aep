/**
* @file
* @brief �ȼ���ֱ���˶���ͷ�ļ�.
* @author ruoxi
*
* �������ȼ���ֱ���˶���.
*/

#ifndef __ACCELERATION_LINEAR_MOTION_H__
#define __ACCELERATION_LINEAR_MOTION_H__

#include "aircraft_measure_ifaces.h"

class AccelerationLinearMotion : public IMotion
{
public:
    enum
    {
        #undef DEFINE_ATTR
        /** @brief �ض����ȼ���ֱ���˶����Ե������DEFINE_ATTR. */
        #define DEFINE_ATTR(a, msg) a,
        /** @brief ���������������acceleration_linear_motion_attrs.hͷ�ļ��Ŀ���. */
        #define __USE_ACCELERATION_LINEAR_MOTION_ATTRS__
        #include "acceleration_linear_motion_attrs.h"
    };

public:
    AccelerationLinearMotion();
    virtual ~AccelerationLinearMotion();

    virtual RC _stdcall GetInterface(UINT32 iid, void **iface);
    virtual RC _stdcall Config();
    virtual RC _stdcall Destroy();
    virtual RC _stdcall GetName(LPWSTR *name);
    virtual RC _stdcall GetAttribute(UINT32 aid, void **attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Validate();

    virtual RC _stdcall GetCurrentVelocity(Vector &velocity);
    virtual RC _stdcall Move(Vector &coordinate, double time);

public:
    Vector *m_Velocity;
    Vector *m_Acceleration;

    LPWSTR m_Name;

    friend AccelerationLinearMotion *AccelerationLinearMotionFactory();
};

extern LPCWSTR AccelerationLinearMotionTypeName;

extern UINT32 AccelerationLinearMotionAttributeList[];

extern UINT32 AccelerationLinearMotionCount;

extern AccelerationLinearMotion *AccelerationLinearMotionFactory();

extern void AccelerationLinearMotionDestroy(AccelerationLinearMotion *accelerationLinearMotion);

#endif // __ACCELERATION_LINEAR_MOTION_H__
