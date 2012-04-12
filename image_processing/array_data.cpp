/**
* @file
* @brief 数组数据类cpp文件.
* @author ruoxi
*
* 实现了数组数据类.
*/

#include "array_data.h"

ArrayData::ArrayData()
:
m_Array(NULL)
{
}

void *ArrayData::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_IDATA == iid)
    {
        iface = static_cast<IData *>(this);
    }
    else if (CLIENT_CIID_ARRAY_DATA == iid)
    {
        iface = static_cast<IArrayData *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}
