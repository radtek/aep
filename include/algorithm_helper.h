/**
* @file
* @brief �㷨��������ͷ�ļ�.
* @author ruoxi
*
* �������㷨��������.
*/

#ifndef __ALGORITHM_HELPER_H__
#define __ALGORITHM_HELPER_H__

#include "algorithm.h"

namespace AlgorithmHelper
{
    typedef bool (*InitializeFunc)(void);
    /** @brief ʵ����DLL�е��㷨��ʼ��������ǰ׺. */
    extern LPCSTR InitializeFuncPrefix;

    /** @brief ʵ����DLL�е���ں�����ǰ׺. */
    extern LPCSTR FuncPrefix;

    typedef void (*TerminateFunc)(void);
    /** @brief ʵ����DLL�е��㷨���ٺ�����ǰ׺. */
    extern LPCSTR TerminateFuncPrefix;

    typedef Algorithm::ParamNameList ParamNameList;
    typedef Algorithm::ParamList ParamList;

    RC GetParamList(const ParamNameList &paramNameList, ComponentList &componentList, ParamList &paramList);
    /** @brief �㷨���и�������. */
    RC RunFunc(wstring dllFileName, wstring funcName, ParamList paramList);
    /** @brief �㷨���и�������. */
    RC RealRunFunc(HINSTANCE algorithmDllHandle, string fullFuncName, ParamList paramList, Param **&output, bool &result);
    RC ReleaseParam(Param *param);
};

#endif // __ALGORITHM_HELPER_H__
