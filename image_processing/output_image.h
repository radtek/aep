/**
* @file
* @brief 输出图像类头文件.
* @author ruoxi
*
* 定义了输出图像类.
*/

#ifndef __OUTPUT_IMAGE_H__
#define __OUTPUT_IMAGE_H__

#include "image_processing_ifaces.h"

class OutputImage : public IOutputFile
{
public:
    OutputImage();
    virtual ~OutputImage();

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
        AAID_OUTPUT_ID1 = 0,
        AAID_OUTPUT_ID2,
        AAID_OUTPUT_ID3,
        AAID_OUTPUT_ID4,
        AAID_OUTPUT_ID5,
        AAID_WIDTH1,
        AAID_WIDTH2,
        AAID_WIDTH3,
        AAID_WIDTH4,
        AAID_WIDTH5,
        AAID_HEIGHT1,
        AAID_HEIGHT2,
        AAID_HEIGHT3,
        AAID_HEIGHT4,
        AAID_HEIGHT5,
        AAID_FILE_PATH1,
        AAID_FILE_PATH2,
        AAID_FILE_PATH3,
        AAID_FILE_PATH4,
        AAID_FILE_PATH5,
        AAID_DEPTH,
        AAID_LAST,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual IComponent * _stdcall Clone();
    virtual void _stdcall Reset();
    virtual RC _stdcall Config();
    virtual RC _stdcall Run();
    virtual RC _stdcall SetInput(IData *input);
    virtual RC _stdcall GetOutput(IData *&output);

public:
    static const UINT32 m_OutputCount = 5;
    UINT32 m_OutputId[m_OutputCount];
    UINT32 m_Width[m_OutputCount];
    UINT32 m_Height[m_OutputCount];
    wstring m_FilePath[m_OutputCount];

    UINT32 m_Depth;

    UINT32 m_Id;
    wstring m_Name;

protected:
    IOutputFileInput *m_Input;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_OUTPUT_IMAGE;
    static OutputImage *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __OUTPUT_IMAGE_H__
