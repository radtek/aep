/**
* @file
* @brief ����ļ���������cpp�ļ�.
* @author ruoxi
*
* ʵ��������ļ�������.
*/

#include "image_processing_ifaces.h"

IOutputFileInput::IOutputFileInput()
:
m_Array(NULL)
{
}

void *IOutputFileInput::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_IDATA == iid)
    {
        iface = static_cast<IData *>(this);
    }
    else if (CLIENT_CIID_OUTPUT_FILE_INPUT == iid)
    {
        iface = this;
    }
    else
    {
        iface = NULL;
    }

    return iface;
}
