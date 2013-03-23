/**
* @file
* @brief 图像窗口类头文件.
* @author ruoxi
*
* 定义了图像类.
*/

#ifndef __EXTERNAL_DATA_SCISSOR_H__
#define __EXTERNAL_DATA_SCISSOR_H__

#include "image_processing_ifaces.h"

class ExternalDataScissor : public IExternalData
{
public:
    ExternalDataScissor();
    virtual ~ExternalDataScissor();

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
        AAID_WIDTH,
        AAID_HEIGHT,
        AAID_CENTER_X,
        AAID_CENTER_Y,
        AAID_OUTPUT_FILE,
        AAID_FROM_ALGORITHM_OUTPUT_INDEX,
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

public:
    UINT32 m_Width;
    UINT32 m_Height;
    INT32 m_CenterX;
    INT32 m_CenterY;
    INT32 m_DeltaX;
    INT32 m_DeltaY;
    wstring m_OutputFile;
    UINT32 m_FromAlgorithmOutputIndex;

    UINT32 m_Id;
    wstring m_Name;

    bool m_FirstRun;

protected:
    IExternalDataOutput *m_ExternalDataInput;
    IExternalDataOutput *m_Output;

public:
    static const CLIENT_CIID s_InterfaceId = CLIENT_CIID_EXTERNAL_DATA;
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_EXTERNAL_DATA_SCISSOR;
    static ExternalDataScissor *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __EXTERNAL_DATA_SCISSOR_H__
