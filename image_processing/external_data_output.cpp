/**
* @file
* @brief 外部数据输出类cpp文件.
* @author ruoxi
*
* 实现了外部数据输出类.
*/

#include "image_processing_ifaces.h"

IExternalDataOutput::IExternalDataOutput()
:
m_Array(NULL)
{
}

void *IExternalDataOutput::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_IDATA == iid)
    {
        iface = static_cast<IData *>(this);
    }
    else if (CLIENT_CIID_EXTERNAL_DATA_OUTPUT == iid)
    {
        iface = this;
    }
    else
    {
        iface = NULL;
    }

    return iface;
}
