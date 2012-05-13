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
    typedef bool (*InitializeFunc)(void);
    /** @brief 实际在DLL中的算法初始化函数名前缀. */
    extern LPCSTR InitializeFuncPrefix;

    /** @brief 实际在DLL中的入口函数名前缀. */
    extern LPCSTR FuncPrefix;

    typedef void (*TerminateFunc)(void);
    /** @brief 实际在DLL中的算法销毁函数名前缀. */
    extern LPCSTR TerminateFuncPrefix;

    Array *CreateDoubleArray(UINT32 x, UINT32 y, const char *content = NULL);
    Array *CreateDoubleArray(UINT32 x, UINT32 y, const double *content);
    void DestroyArray(Array *a);

    RC RunFunc(wstring dllFileName, wstring funcName, vector<Array *> inputList, Array **output);
    RC RealRunFunc(HINSTANCE algorithmDllHandle, string fullFuncName, vector<Array *> inputList, Array **&output, bool &result);
};

#endif // __MATLAB_HELPER_H__
