/**
* @file
* @brief ͼ�������ͷ�ļ�.
* @author ruoxi
*
* ������ͼ�������.
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
