#include "image_processing_ifaces.h"

IImageAlgorithmOutput::IImageAlgorithmOutput(UINT32 size, IImageAlgorithm *imageAlgorithm)
: m_Size(size)
, m_ImageAlgorithm(imageAlgorithm)
{
    m_Array = new Array *[m_Size];
    for (UINT32 i = 0; i < m_Size; ++i)
    {
        m_Array[i] = 0;
    }
}

void *IImageAlgorithmOutput::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_IDATA == iid)
    {
        iface = static_cast<IData *>(this);
    }
    else if (CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT == iid)
    {
        iface = this;
    }
    else
    {
        iface = NULL;
    }

    return iface;
}

void IImageAlgorithmOutput::Reset()
{
    for (UINT32 i = 0; i < m_Size; ++i)
    {
        m_Array[i] = 0;
    }
}
