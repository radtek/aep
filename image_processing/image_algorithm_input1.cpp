#include "image_processing_ifaces.h"

void *IImageAlgorithmInput1::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_IDATA == iid)
    {
        iface = static_cast<IData *>(this);
    }
    else if (CLIENT_CIID_IMAGE_ALGORITHM_INPUT1 == iid)
    {
        iface = this;
    }
    else
    {
        iface = NULL;
    }

    return iface;
}
