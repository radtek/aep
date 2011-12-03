/**
* @file
* @brief ��������ͷ�ļ�.
* @author ruoxi
*
* �����˷�������.
*/

#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "aircraft_component_ifaces.h"

class Aircraft : public IAircraft
{
public:
    Aircraft();
    virtual ~Aircraft();

    virtual void _stdcall Destroy();
    virtual void * _stdcall GetInterface(UINT32 iid);
    virtual UINT32 _stdcall GetId();
    virtual void _stdcall SetId(UINT32 id);
    virtual wstring _stdcall GetName();
    virtual void _stdcall SetName(wstring name);
    virtual RC _stdcall GetAttribute(UINT32 aid, void **attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual Param * _stdcall ToParam();
    virtual UINT32 _stdcall GetParamSize();

    virtual void _stdcall Fly(double time);

public:
    Vector m_Coordinate;

    IMotion *m_Motion;

    UINT32 m_Id;
    wstring m_Name;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_AIRCRAFT;
    static Aircraft *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __AIRCRAFT_H__