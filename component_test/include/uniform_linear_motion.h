/**
* @file
* @brief 匀速直线运动类头文件.
* @author ruoxi
*
* 定义了匀速直线运动类.
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
        /** @brief 重定义匀速直线运动属性的外包宏DEFINE_ATTR. */
        #define DEFINE_ATTR(a, msg) a,
        /** @brief 用来开启允许包含uniform_linear_motion_attrs.h头文件的开关. */
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
