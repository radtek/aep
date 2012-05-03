/**
* @file
* @brief MatLab��������ͷ�ļ�.
* @author ruoxi
*
* ������MatLab��������.
*/

#ifndef __MATLAB_HELPER_H__
#define __MATLAB_HELPER_H__

#include "algorithm.h"

typedef mxArray Array;

namespace MatLabHelper
{
    Array *CreateDoubleArray(UINT32 x, UINT32 y, const char *content = NULL);
    void DestroyArray(Array *a);
};

#endif // __MATLAB_HELPER_H__
