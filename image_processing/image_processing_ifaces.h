/**
* @file
* @brief 图像处理接口头文件.
* @author ruoxi
*
* 定义了图像处理中的全部接口.
*/

#ifndef __IMAGE_PROCESSING_IFACES_H__
#define __IMAGE_PROCESSING_IFACES_H__

#include "interfaces.h"
#include "vector.h"
#include "iarc.h"

BEGIN_CLIENT_CIID
    CLIENT_CIID_EXTERNAL_DATA,
    CLIENT_CIID_EXTERNAL_DATA_OUTPUT,
    CLIENT_CIID_IMAGE,
    CLIENT_CIID_IMAGE_OUTPUT,
    CLIENT_CIID_IMAGE_ALGORITHM,
    CLIENT_CIID_IMAGE_ALGORITHM_INPUT1,
    CLIENT_CIID_IMAGE_ALGORITHM_INPUT2,
    CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT1,
    CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT2,
    CLIENT_CIID_EVALUATE,
END_CLIENT_CIID

BEGIN_CLIENT_CCID
    CLIENT_CCID_EXTERNAL_DATA,
    CLIENT_CCID_IMAGE,
    CLIENT_CCID_ADD,
    CLIENT_CCID_SUB,
    CLIENT_CCID_EVALUATE,
END_CLIENT_CCID

typedef mxArray Array;

struct IExternalData : IComponent
{
};

struct IExternalDataOutput : IData
{
    virtual void * _stdcall GetInterface(UINT32 iid);
    Array *m_Array;
};

struct IImage : IComponent
{
};

struct IImageOutput : IData
{
    virtual void * _stdcall GetInterface(UINT32 iid);
    Array *m_Array;
};

struct IImageAlgorithm : IComponent
{
    virtual IARC _stdcall Run() = 0;
};

struct IImageAlgorithmInput1 : IData
{
    virtual void * _stdcall GetInterface(UINT32 iid);
    const Array *m_Array;
};

struct IImageAlgorithmInput2 : IData
{
    virtual void * _stdcall GetInterface(UINT32 iid);
    const Array *m_Array;
};

struct IImageAlgorithmOutput1 : IData
{
    virtual void * _stdcall GetInterface(UINT32 iid);
    Array *m_Array;
};

struct IImageAlgorithmOutput2 : IData
{
    virtual void * _stdcall GetInterface(UINT32 iid);
    Array *m_Array;
};

#endif // __IMAGE_PROCESSING_IFACES_H__
