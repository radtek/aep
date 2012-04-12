/**
* @file
* @brief 图像输出类cpp文件.
* @author ruoxi
*
* 实现了图像输出类.
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
