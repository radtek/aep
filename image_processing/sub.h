/**
* @file
* @brief 减法类头文件.
* @author ruoxi
*
* 定义了减法类.
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
        AAID_SUB_FACTOR1 = 0,
        AAID_SUB_FACTOR2,
        AAID_SUB_FACTOR3,
        AAID_SUB_FACTOR4,
        AAID_SUB_FACTOR5,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual IComponent * _stdcall Clone();
    virtual void _stdcall Reset();
    virtual RC _stdcall Config();
    virtual RC _stdcall SetInput(IData *input);
    virtual RC _stdcall GetOutput(IData *&output);

    virtual RC _stdcall Run();

protected:
    IImageAlgorithmInput1 *m_Input1;
    IImageAlgorithmInput2 *m_Input2;
    static const UINT32 m_OutputCount = 5;
    IImageAlgorithmOutput *m_Output;

public:
    double m_SubFactor[m_OutputCount];

    UINT32 m_Id;
    wstring m_Name;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_SUB;
    static Sub *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __SUB_H__
