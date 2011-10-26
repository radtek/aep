/**
* @file
* @brief ����ֱ���˶���ͷ�ļ�.
* @author ruoxi
*
* ����������ֱ���˶���.
*/

#ifndef __UNIFORM_LINEAR_MOTION_H__
#define __UNIFORM_LINEAR_MOTION_H__

#include "aircraft_measure_ifaces.h"

class UniformLinearMotion : public IMotion
{
public:
    enum
    {
        #undef DEFINE_ATTR
        /** @brief �ض�������ֱ���˶����Ե������DEFINE_ATTR. */
        #define DEFINE_ATTR(a, msg) a,
        /** @brief ���������������uniform_linear_motion_attrs.hͷ�ļ��Ŀ���. */
        #define __USE_UNIFORM_LINEAR_MOTION_ATTRS__
        #include "uniform_linear_motion_attrs.h"
    };

public:
    UniformLinearMotion();
    virtual ~UniformLinearMotion();

    virtual RC _stdcall GetInterface(UINT32 iid, void **iface);
    virtual RC _stdcall GetName(LPWSTR *name);
    virtual RC _stdcall GetAttribute(UINT32 aid, void **attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);

    virtual RC _stdcall GetCurrentVelocity(Vector &velocity);
    virtual RC _stdcall Move(Vector &coordinate, double time);
private:
    Vector *m_Velocity;

    LPWSTR m_Name;

    friend UniformLinearMotion *UniformLinearMotionFactory();
};

extern LPCWSTR UniformLinearMotionTypeName;

extern UINT32 UniformLinearMotionAttributeList[];

extern UINT32 UniformLinearMotionCount;

extern UniformLinearMotion *UniformLinearMotionFactory();

#endif // __UNIFORM_LINEAR_MOTION_H__
