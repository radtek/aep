#ifndef __GLOBAL_VAR_H__
#define __GLOBAL_VAR_H__

#include "image_processing_ifaces.h"

class GlobalVar : IGlobalVar
{
public:
    GlobalVar();
    virtual ~GlobalVar();

    virtual UINT32 _stdcall GetInterfaceTypeId();
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
        AAID_COUNT,
        AAID_WIDTH,
        AAID_HEIGHT,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual IComponent * _stdcall Clone();
    virtual void _stdcall Reset();
    virtual RC _stdcall Config();
    virtual RC _stdcall Run(bool input = true);
    virtual RC _stdcall SetInput(IData *input);
    virtual RC _stdcall GetOutput(IData *&output);

    virtual Array * _stdcall GetData();
    virtual void _stdcall SetData(Array *data);

public:
    UINT32 m_Count;
    UINT32 m_Width, m_Height;

    Array *m_Array;

    UINT32 m_Id;
    wstring m_Name;

public:
    static const CIID s_InterfaceId = CIID_IGLOBAL_VAR;
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_GLOBAL_VAR;
    static GlobalVar *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __GLOBAL_VAR_H__
