/**
* @file
* @brief 图像输出类头文件.
* @author ruoxi
*
* 定义了图像输出类.
*/

#ifndef __IMAGE_OUTPUT_H__
#define __IMAGE_OUTPUT_H__

#include "image_processing_ifaces.h"

class ImageOutput : IImageOutput
{
public:
    ImageOutput();

    void * _stdcall GetInterface(UINT32 iid);

    Array *m_Array;
};

#endif // __IMAGE_OUTPUT_H__
