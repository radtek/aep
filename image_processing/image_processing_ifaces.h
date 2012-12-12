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
    CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT,
    CLIENT_CIID_OUTPUT_FILE,
    CLIENT_CIID_OUTPUT_FILE_INPUT,
    CLIENT_CIID_OUTPUT_FILE_OUTPUT,
    CLIENT_CIID_TRANSFER,
    CLIENT_CIID_TRANSFER_INPUT,
END_CLIENT_CIID

BEGIN_CLIENT_CCID
    CLIENT_CCID_EXTERNAL_DATA,
    CLIENT_CCID_IMAGE,
    CLIENT_CCID_DAT_IMAGE,
    CLIENT_CCID_IMAGE_ALGORITHM,
    CLIENT_CCID_ADD,
    CLIENT_CCID_SUB,
    CLIENT_CCID_OUTPUT_EXTERNAL_DATA,
    CLIENT_CCID_OUTPUT_IMAGE,
    CLIENT_CCID_EVALUATE,
    CLIENT_CCID_EXTERNAL_DATA_SCISSOR,
    CLIENT_CCID_IMAGE_SCISSOR,
    CLIENT_CCID_EXTERNAL_DATA_BATCH,
    CLIENT_CCID_IMAGE_BATCH,
    CLIENT_CCID_DAT_IMAGE_BATCH,
    CLIENT_CCID_OUTPUT_EXTERNAL_DATA_BATCH,
    CLIENT_CCID_OUTPUT_IMAGE_BATCH,
    CLIENT_CCID_TRANSFER_FILE,
    CLIENT_CCID_ALGORITHM_EVALUATE,
END_CLIENT_CCID

typedef mxArray Array;

struct IExternalData : IComponent
{
};

struct IExternalDataOutput : IData
{
    IExternalDataOutput();
    virtual void * _stdcall GetInterface(UINT32 iid);
    Array *m_Array;
};

struct IImage : IComponent
{
};

struct IImageOutput : IData
{
    IImageOutput();
    virtual void * _stdcall GetInterface(UINT32 iid);
    Array *m_Array;
};

struct IImageAlgorithm : IAlgorithm
{
};

struct IImageAlgorithmInput1 : IData
{
    IImageAlgorithmInput1();
    virtual void * _stdcall GetInterface(UINT32 iid);
    Array *m_Array;
};

struct IImageAlgorithmInput2 : IData
{
    IImageAlgorithmInput2();
    virtual void * _stdcall GetInterface(UINT32 iid);
    Array *m_Array;
};

struct IImageAlgorithmOutput : IData
{
    IImageAlgorithmOutput(UINT32 size, IImageAlgorithm *imageAlgorithm = NULL);
    virtual void * _stdcall GetInterface(UINT32 iid);
    void Reset();
    Array **m_Array;
    UINT32 m_Size;
    IImageAlgorithm *m_ImageAlgorithm;
};

struct IOutputFile : IComponent
{
};

struct IOutputFileInput : IData
{
    IOutputFileInput(UINT32 size);
    virtual void * _stdcall GetInterface(UINT32 iid);
    void Reset();
    Array **m_Array;
    UINT32 m_Size;
};

struct IOutputFileOutput : IData
{
    IOutputFileOutput();
    virtual void * _stdcall GetInterface(UINT32 iid);
    void Reset();
    vector<wstring> m_Path;
};

struct ITransfer : IComponent
{
};

struct ITransferInput : IData
{
    ITransferInput();
    virtual void * _stdcall GetInterface(UINT32 iid);
    void Reset();
    vector<wstring> m_Path;
};

extern PlatformService *g_PlatformService;

#endif // __IMAGE_PROCESSING_IFACES_H__
