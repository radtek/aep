/**
* @file
* @brief ������ͷ�ļ�.
* @author ruoxi
*
* �����˼�����.
*/

#ifndef __SUB_H__
#define __SUB_H__

#include "image_processing_ifaces.h"

class Sub : public IImageAlgorithm
{
public:
    Sub();
    virtual ~Sub();

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
        AAID_TEST_PARAM,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual bool _stdcall SetInput(IData *data);
    virtual IData *GetOutput();

    virtual IARC _stdcall Run();

public:
    double m_TestParam;

    UINT32 m_Id;
    wstring m_Name;

protected:
    IExternalDataOutput *m_ExternalData;
    IImageOutput *m_Input;
    IImageOutput *m_Output;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_SUB;
    static Sub *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __SUB_H__
