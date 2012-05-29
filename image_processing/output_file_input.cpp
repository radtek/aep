/**
* @file
* @brief ����ļ���������cpp�ļ�.
* @author ruoxi
*
* ʵ��������ļ�������.
*/

#include "image_processing_ifaces.h"

IOutputFileInput::IOutputFileInput(UINT32 size)
:
m_Size(size)
{
    m_Array = new Array *[m_Size];
    for (UINT32 i = 0; i < m_Size; ++i)
    {
        m_Array[i] = 0;
    }
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

void IOutputFileInput::Reset()
{
    for (UINT32 i = 0; i < m_Size; ++i)
    {
        m_Array[i] = 0;
    }
}