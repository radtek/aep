#include "image_processing_ifaces.h"

IImageAlgorithmInput2::IImageAlgorithmInput2()
:
m_Array(NULL)
{
}

void *IImageAlgorithmInput2::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_IDATA == iid)
    {
        iface = static_cast<IData *>(this);
    }
    else if (CLIENT_CIID_IMAGE_ALGORITHM_INPUT2 == iid)
    {
        iface = this;
    }
    else
    {
        iface = NULL;
    }

    return iface;
}
