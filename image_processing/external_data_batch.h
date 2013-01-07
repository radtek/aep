/**
* @file
* @brief 外部数据类头文件.
* @author ruoxi
*
* 定义了外部数据类.
*/

#ifndef __EXTERNAL_DATA_BATCH_H__
#define __EXTERNAL_DATA_BATCH_H__

#include "external_data.h"

class ExternalDataBatch : public ExternalData
{
public:
    ExternalDataBatch();
    virtual ~ExternalDataBatch();

    virtual UINT32 _stdcall GetTypeId();
    virtual void _stdcall Save(CArchive &ar);
    virtual void _stdcall Load(CArchive &ar);
    enum AAID
    {
        AAID_START_ID = ExternalData::AAID_LAST,
        AAID_END_ID,
        AAID_LAST,
    };
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);

    virtual IComponent * _stdcall Clone();
    virtual RC _stdcall Config();
    virtual RC _stdcall Run(bool input = true);

public:
    UINT32 m_StartId, m_EndId, m_CurrentId;

public:
    static const CLIENT_CCID s_ComponentId = CLIENT_CCID_EXTERNAL_DATA_BATCH;
    static ExternalDataBatch *Factory();
    static LPCWSTR s_ComponentName;
    static UINT32 s_Count;
};

#endif // __EXTERNAL_DATA_BATCH_H__
