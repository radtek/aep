/**
* @file
* @brief 算法相关函数cpp文件.
* @author ruoxi
*
* 实现了算法相关函数.
*/

#include "stdafx.h"

#include "algorithm.h"
#include "utility.h"

#include "mclmcrrt.h"
#include "mclcppclass.h"

RC Algorithm::Init()
{
    RC rc;

    if (!mclInitializeApplication(NULL, 0))
    {
        return RC::ALGORITHM_INIT_ERROR;
    }

    return rc;
}

RC Algorithm::Shut()
{
    RC rc;

    if (!mclTerminateApplication())
    {
        return RC::ALGORITHM_SHUT_ERROR;
    }

    return rc;
}

RC Algorithm::RegisterAlgorithm(LPCWSTR algorithmCfgFileName,
                                AlgorithmInfoList &algorithmInfoList)
{
    RC rc;

    // FIXME: 加法
    AlgorithmInfo algorithmInfo;
    algorithmInfo.name = TEXT("加法");
    algorithmInfo.dllFileName = TEXT("AddFunc.dll");
    algorithmInfo.funcName = "AddFunc";
    algorithmInfoList.push_back(algorithmInfo);

    return rc;
}

RC Algorithm::AddAlgorithm(const AlgorithmInfo &algorithmInfo)
{
    RC rc;

    return rc;
}

RC Algorithm::RunAlgorithm(const AlgorithmInfo &algorithmInfo)
{
    RC rc;

    HINSTANCE algorithmDllHandle = LoadLibrary(algorithmInfo.dllFileName);

    if (!algorithmDllHandle)
    {
        Utility::PromptLastErrorMessage();
        return RC::ALGORITHM_LOADDLL_ERROR;
    }

    bool result;

    string initializeFuncName = algorithmInfo.funcName;
    initializeFuncName += InitializeFuncPrefix;

    InitializeFunc initializeFunc = (InitializeFunc)GetProcAddress(
        (HMODULE)algorithmDllHandle,
        initializeFuncName.c_str());

    if (!initializeFunc)
    {
        Utility::PromptLastErrorMessage();
        return RC::ALGORITHM_GETPROC_ERROR;
    }

    result = initializeFunc();

    if (!result)
    {
        return RC::ALGORITHM_RUN_INITIALIZE_ERROR;
    }

    string funcName = FuncPrefix;
    funcName += algorithmInfo.funcName;

    Func func = (Func)GetProcAddress(
        (HMODULE)algorithmDllHandle,
        funcName.c_str());

    if (!func)
    {
        Utility::PromptLastErrorMessage();
        return RC::ALGORITHM_GETPROC_ERROR;
    }

    // FIXME.
    /*
    mxArray *f,
    *a = mxCreateDoubleMatrix_730(1, 1, mxREAL),
    *b = mxCreateDoubleMatrix_730(1, 1, mxREAL);
    */
    result = func(0, NULL, NULL, NULL);
    if (!result)
    {
        return RC::ALGORITHM_RUN_ERROR;
    }

        string terminateFuncName = algorithmInfo.funcName;
    terminateFuncName += TerminateFuncPrefix;

    TerminateFunc terminateFunc = (TerminateFunc)GetProcAddress(
        (HMODULE)algorithmDllHandle,
        terminateFuncName.c_str());

    if (!terminateFunc)
    {
        Utility::PromptLastErrorMessage();
        return RC::ALGORITHM_GETPROC_ERROR;
    }

    terminateFunc();

    return rc;
}

LPCSTR Algorithm::InitializeFuncPrefix = "Initialize";

LPCSTR Algorithm::FuncPrefix = "mlf";

LPCSTR Algorithm::TerminateFuncPrefix = "Terminate";