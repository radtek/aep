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
    /** @brief 实际在DLL中的算法初始化函数名前缀. */
    extern LPCSTR InitializeFuncPrefix;

    /** @brief 实际在DLL中的入口函数名前缀. */
    extern LPCSTR FuncPrefix;

    typedef void (*TerminateFunc)(void);
    /** @brief 实际在DLL中的算法销毁函数名前缀. */
    extern LPCSTR TerminateFuncPrefix;

    typedef Algorithm::ParamNameList ParamNameList;
    typedef Algorithm::ParamList ParamList;

    RC GetParamList(const ParamNameList &paramNameList, ComponentList &componentList, ParamList &paramList);
    /** @brief 算法运行辅助函数. */
    RC RunFunc(wstring dllFileName, wstring funcName, ParamList paramList);
    /** @brief 算法运行辅助函数. */
    RC RealRunFunc(HINSTANCE algorithmDllHandle, string fullFuncName, ParamList paramList, Param **&output, bool &result);
    RC ReleaseParam(Param *param);
};

#endif // __ALGORITHM_HELPER_H__
