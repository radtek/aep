/**
* @file
* @brief 加法类头文件.
* @author ruoxi
*
* 定义了加法类.
*/

#ifndef __ADD_H__
#define __ADD_H__

#include "image_processing_ifaces.h"

class Add : public IImageAlgorithm
{
public:
    Add();
    virtual ~Add();

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
        AAID_ADD_FACTOR,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual RC _stdcall Config();
    virtual RC _stdcall SetInput(IData *data);
    virtual RC _stdcall GetOutput1(IData *&output);
    virtual RC _stdcall GetOutput2(IData *&output);

    virtual IARC _stdcall Run();

public:
    double m_AddFactor;

    UINT32 m_Id;
    wstring m_Name;

protected:
    IImageAlgorithmInput1 *m_Input1;
    IImageAlgorithmInput2 *m_Input2;
    IImageAlgorithmOutput1 *m_Output1;
    IImageAlgorithmOutput2 *m_Output2;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_ADD;
    static Add *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __ADD_H__
