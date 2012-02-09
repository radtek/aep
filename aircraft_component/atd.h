#ifndef __ATD_H__
#define __ATD_H__

#include "aircraft_component_ifaces.h"

class ATD : public IRealValue
{
public:
    ATD();
    virtual ~ATD();

    virtual UINT32 _stdcall GetTypeId();
    virtual void _stdcall Save(CArchive &ar);
    virtual void _stdcall Load(CArchive &ar);
    virtual void _stdcall Destroy();
    virtual void * _stdcall GetInterface(UINT32 iid);
    virtual UINT32 _stdcall GetId();
    virtual void _stdcall SetId(UINT32 id);
    virtual wstring _stdcall GetName();
    virtual void _stdcall SetName(wstring name);
    enum AAID
    {
        AAID_STEP,
        AAID_TIME,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual Param * _stdcall ToParam();
    virtual UINT32 _stdcall GetParamSize();
    virtual RC _stdcall DrawFigure(Engine *engine);

public:
    double m_Step;
    double m_Time;

    IAircraft *m_Aircraft;
    ITarget *m_Target;

    UINT32 m_Id;
    wstring m_Name;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_ATD;
    static ATD *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __ATD_H__
