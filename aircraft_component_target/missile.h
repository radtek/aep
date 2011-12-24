/**
* @file
* @brief 导弹类头文件.
* @author ruoxi
*
* 定义了导弹类.
*/

#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "aircraft_component_ifaces.h"

class Missile : public ITarget
{
public:
    Missile();
    virtual ~Missile();

    virtual UINT32 _stdcall GetTypeId();
    virtual void Save(CArchive &ar);
    virtual void Load(CArchive &ar);
    virtual void _stdcall Destroy();
    virtual void * _stdcall GetInterface(UINT32 iid);
    virtual UINT32 _stdcall GetId();
    virtual void _stdcall SetId(UINT32 id);
    virtual wstring _stdcall GetName();
    virtual void _stdcall SetName(wstring name);
    enum AAID
    {
        AAID_COORD_X,
        AAID_COORD_Y,
        AAID_COORD_Z,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
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
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_MISSILE;
    static Missile *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __MISSILE_H__
