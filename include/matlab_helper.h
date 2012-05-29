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

    typedef void (*PrintStackFunc)(void);
    extern LPCSTR PrintStackFuncPrefix;

    typedef void (*TerminateFunc)(void);
    /** @brief ʵ����DLL�е��㷨���ٺ�����ǰ׺. */
    extern LPCSTR TerminateFuncPrefix;

    Array *CreateDoubleArray(UINT32 x, UINT32 y, const char *content = NULL, UINT32 size = 0);
    Array *CreateDoubleArray(UINT32 x, UINT32 y, const double *content, UINT32 size = 0);
    void DestroyArray(Array *a);

    RC RunFunc(wstring dllFileName, wstring funcName, UINT32 outputCount, Array **output, const vector<Array *> &inputList);
    RC RealRunFunc(HINSTANCE algorithmDllHandle, string fullFuncName, UINT32 outputCount, Array **output, const vector<Array *> &inputList, bool &result);
};

#endif // __MATLAB_HELPER_H__
