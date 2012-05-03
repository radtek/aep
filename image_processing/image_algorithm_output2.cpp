#include "image_processing_ifaces.h"

IImageAlgorithmOutput2::IImageAlgorithmOutput2()
:
m_Array(NULL)
{
}

void *IImageAlgorithmOutput2::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_IDATA == iid)
    {
        iface = static_cast<IData *>(this);
    }
    else if (CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT2 == iid)
    {
        iface = this;
    }
    else
    {
        iface = NULL;
    }

    return iface;
}
