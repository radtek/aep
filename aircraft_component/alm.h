/**
* @file
* @brief 飞行器类头文件.
* @author ruoxi
*
* 定义了飞行器类.
*/

#ifndef __ALM_H__
#define __ALM_H__

#include "aircraft_component_ifaces.h"

class ALM : public IMotion 
{
public:
    ALM();
    virtual ~ALM();

    virtual void _stdcall Destroy();
    virtual void * _stdcall GetInterface(UINT32 iid);
    virtual UINT32 _stdcall GetId();
    virtual void _stdcall SetId(UINT32 id);
    virtual wstring _stdcall GetName();
    virtual void _stdcall SetName(wstring name);
    virtual RC _stdcall GetAttribute(UINT32 aid, void **attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual void _stdcall Move(Vector &coordinate, double time);

public:
    Vector m_Velocity;
    Vector m_Acceleration;

    UINT32 m_Id;
    wstring m_Name;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_ALM;
    static ALM *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __ALM_H__
