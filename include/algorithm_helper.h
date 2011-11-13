/**
* @file
* @brief 算法辅助函数头文件.
* @author ruoxi
*
* 定义了算法辅助函数.
*/

#ifndef __ALGORITHM_HELPER_H__
#define __ALGORITHM_HELPER_H__

#include "algorithm.h"

namespace AlgorithmHelper
{
    typedef bool (*InitializeFunc)(void);
    extern LPCSTR InitializeFuncPrefix;

    extern LPCSTR FuncPrefix;

    typedef void (*TerminateFunc)(void);
    extern LPCSTR TerminateFuncPrefix;

    typedef Algorithm::ParamNameList ParamNameList;
    typedef Algorithm::ParamList ParamList;

    RC GetParamList(const ParamNameList &paramNameList, ComponentList &componentList, ParamList &paramList);
    RC RunFunc(wstring dllFileName, wstring funcName, ParamList paramList);
    RC RealRunFunc(HINSTANCE algorithmDllHandle, string fullFuncName, ParamList paramList, Param **&output, bool &result);
    RC ReleaseParam(Param *param);
};

#endif // __ALGORITHM_HELPER_H__
