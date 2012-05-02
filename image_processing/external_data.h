/**
* @file
* @brief 外部数据类头文件.
* @author ruoxi
*
* 定义了外部数据类.
*/

#ifndef __EXTERNAL_DATA_H__
#define __EXTERNAL_DATA_H__

#include "image_processing_ifaces.h"

class ExternalData : public IExternalData
{
public:
    ExternalData();
    virtual ~ExternalData();

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
        AAID_FILE_PATH,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual RC _stdcall SetInput(IData *input);
    virtual RC _stdcall GetOutput1(IData *&output);
    virtual RC _stdcall GetOutput2(IData *&output);

public:
    wstring m_FilePath;

    UINT32 m_Id;
    wstring m_Name;

protected:
    IExternalDataOutput *m_Output;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_EXTERNAL_DATA;
    static ExternalData *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __EXTERNAL_DATA_H__
