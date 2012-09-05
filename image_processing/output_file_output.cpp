/**
* @file
* @brief ����ļ���������cpp�ļ�.
* @author ruoxi
*
* ʵ��������ļ�������.
*/

#include "image_processing_ifaces.h"

IOutputFileOutput::IOutputFileOutput()
{
}

void *IOutputFileOutput::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_IDATA == iid)
    {
        iface = static_cast<IData *>(this);
    }
    else if (CLIENT_CIID_OUTPUT_FILE_OUTPUT == iid)
    {
        iface = this;
    }
    else
    {
        iface = NULL;
    }

    return iface;
}

void IOutputFileOutput::Reset()
{
    m_Path.clear();
}
