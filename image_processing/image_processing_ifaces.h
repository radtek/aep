/**
* @file
* @brief ͼ����ӿ�ͷ�ļ�.
* @author ruoxi
*
* ������ͼ�����е�ȫ���ӿ�.
*/

#ifndef __IMAGE_PROCESSING_IFACES_H__
#define __IMAGE_PROCESSING_IFACES_H__

#include "interfaces.h"
#include "vector.h"
#include "iarc.h"

BEGIN_CLIENT_CIID
    CLIENT_CIID_ARRAY_DATA,
    CLIENT_CIID_EXTERNAL_DATA,
    CLIENT_CIID_IMAGE,
    CLIENT_CIID_IMAGE_ALGORITHM,
    CLIENT_CIID_EVALUATE,
END_CLIENT_CIID

BEGIN_CLIENT_CCID
    CLIENT_CCID_EXTERNAL_DATA,
    CLIENT_CCID_IMAGE,
    CLIENT_CCID_ADD,
    CLIENT_CCID_SUB,
    CLIENT_CCID_EVALUATE,
END_CLIENT_CCID

struct IArrayData : IData
{
};

struct IExternalData : IComponent
{
};

struct IImage : IComponent
{
};

struct IImageAlgorithm : IComponent
{
    virtual IARC _stdcall Run() = 0;
};

#endif // __IMAGE_PROCESSING_IFACES_H__
