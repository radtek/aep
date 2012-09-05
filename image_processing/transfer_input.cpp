/**
* @file
* @brief ����ļ���������cpp�ļ�.
* @author ruoxi
*
* ʵ��������ļ�������.
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
