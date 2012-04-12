/**
* @file
* @brief ����������ͷ�ļ�.
* @author ruoxi
*
* ����������������.
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
