/**
* @file
* @brief 数组数据类头文件.
* @author ruoxi
*
* 定义了数组数据类.
*/

#ifndef __ARRAY_DATA_H__
#define __ARRAY_DATA_H__

#include "image_processing_ifaces.h"

typedef mxArray Array;

class ArrayData : IArrayData
{
public:
    ArrayData();

    void * _stdcall GetInterface(UINT32 iid);

    Array *m_Array;
};

#endif // __ARRAY_DATA_H__
