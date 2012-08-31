/**
* @file
* @brief 外部数据类头文件.
* @author ruoxi
*
* 定义了外部数据类.
*/

#ifndef __OUTPUT_IMAGE_BATCH_H__
#define __OUTPUT_IMAGE_BATCH_H__

#include "output_image.h"

class OutputImageBatch : public OutputImage
{
public:
    OutputImageBatch();
    virtual ~OutputImageBatch();

    virtual UINT32 _stdcall GetTypeId();
    virtual void _stdcall Save(CArchive &ar);
    virtual void _stdcall Load(CArchive &ar);
    enum AAID
    {
        AAID_START_ID = OutputImage::AAID_LAST,
        AAID_END_ID,
        AAID_LAST,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);

    virtual IComponent * _stdcall Clone();
    virtual RC _stdcall Config();
    virtual RC _stdcall Run();

public:
    UINT32 m_StartId, m_EndId, m_CurrentId;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_OUTPUT_IMAGE_BATCH;
    static OutputImageBatch *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __OUTPUT_IMAGE_BATCH_H__
