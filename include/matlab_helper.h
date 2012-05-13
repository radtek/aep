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
    typedef bool (*InitializeFunc)(void);
    /** @brief ʵ����DLL�е��㷨��ʼ��������ǰ׺. */
    extern LPCSTR InitializeFuncPrefix;

    /** @brief ʵ����DLL�е���ں�����ǰ׺. */
    extern LPCSTR FuncPrefix;

    typedef void (*TerminateFunc)(void);
    /** @brief ʵ����DLL�е��㷨���ٺ�����ǰ׺. */
    extern LPCSTR TerminateFuncPrefix;

    Array *CreateDoubleArray(UINT32 x, UINT32 y, const char *content = NULL);
    Array *CreateDoubleArray(UINT32 x, UINT32 y, const double *content);
    void DestroyArray(Array *a);

    RC RunFunc(wstring dllFileName, wstring funcName, vector<Array *> inputList, Array **output);
    RC RealRunFunc(HINSTANCE algorithmDllHandle, string fullFuncName, vector<Array *> inputList, Array **&output, bool &result);
};

#endif // __MATLAB_HELPER_H__
