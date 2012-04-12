/**
* @file
* @brief ͼ�������cpp�ļ�.
* @author ruoxi
*
* ʵ����ͼ�������.
*/

#include "image_output.h"

ImageOutput::ImageOutput()
:
m_Array(NULL)
{
}

void *ImageOutput::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_IDATA == iid)
    {
        iface = static_cast<IData *>(this);
    }
    else if (CLIENT_CIID_IMAGE_OUTPUT == iid)
    {
        iface = static_cast<IImageOutput *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}
