/**
* @file
* @brief �ⲿ���������cpp�ļ�.
* @author ruoxi
*
* ʵ�����ⲿ���������.
*/

#include "external_data_output.h"

/*
ExternalDataOutput::ExternalDataOutput()
:
m_Array(NULL)
{
}

void *ExternalDataOutput::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_IDATA == iid)
    {
        iface = static_cast<IData *>(this);
    }
    else if (CLIENT_CIID_EXTERNAL_DATA_OUTPUT == iid)
    {
        iface = static_cast<IExternalDataOutput *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}
*/

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
