/**
* @file
* @brief 输出文件据输入类cpp文件.
* @author ruoxi
*
* 实现了输出文件输入类.
*/

#include "image_processing_ifaces.h"

ITransferInput ::ITransferInput()
{
}

void *ITransferInput::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_IDATA == iid)
    {
        iface = static_cast<IData *>(this);
    }
    else if (CLIENT_CIID_TRANSFER_INPUT == iid)
    {
        iface = this;
    }
    else
    {
        iface = NULL;
    }

    return iface;
}

void ITransferInput::Reset()
{
    m_Path.clear();
}
