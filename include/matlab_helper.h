/**
* @file
* @brief MatLab辅助函数头文件.
* @author ruoxi
*
* 定义了MatLab辅助函数.
*/

#ifndef __MATLAB_HELPER_H__
#define __MATLAB_HELPER_H__

#include "algorithm.h"

typedef mxArray Array;

namespace MatLabHelper
{
    Array *CreateDoubleArray(UINT32 size, double *content = NULL);
};

#endif // __MATLAB_HELPER_H__
