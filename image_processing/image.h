/**
* @file
* @brief 图像类头文件.
* @author ruoxi
*
* 定义了图像类.
*/

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "image_processing_ifaces.h"

class Image : public IImage
{
public:
    Image();
    virtual ~Image();

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

    virtual IComponent * _stdcall Clone();
    virtual RC _stdcall Config();
    virtual RC _stdcall SetInput(IData *input);
    virtual RC _stdcall GetOutput1(IData *&output);
    virtual RC _stdcall GetOutput2(IData *&output);

public:
    wstring m_FilePath;

    UINT32 m_Id;
    wstring m_Name;

protected:
    IImageOutput *m_Output;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_IMAGE;
    static Image *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __IMAGE_H__
