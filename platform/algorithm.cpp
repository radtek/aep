/**
* @file
* @brief 算法相关函数cpp文件.
* @author ruoxi
*
* 实现了算法相关函数.
*/

#include "algorithm.h"
#include "utility.h"

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

LPCSTR Algorithm::InitializeFuncPrefix = "Initialize";

LPCSTR Algorithm::FuncPrefix = "mlf";

LPCSTR Algorithm::TerminateFuncPrefix = "Terminate";

Algorithm::Algorithm(wstring name, wstring dllFileName, wstring funcName, wstring iconFileName)
:
m_Name(name),
m_DllFileName(dllFileName),
m_FuncName(funcName),
m_IconFileName(iconFileName)
{
}

RC Algorithm::Run()
{
    RC rc;

    HINSTANCE algorithmDllHandle = LoadLibrary(m_DllFileName.c_str());

    if (!algorithmDllHandle)
    {
        Utility::PromptLastErrorMessage();
        return RC::ALGORITHM_LOADDLL_ERROR;
    }

    bool result;

    string initializeFuncName(m_FuncName.begin(), m_FuncName.end());
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
    funcName += string(m_FuncName.begin(), m_FuncName.end());

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

    string terminateFuncName(m_FuncName.begin(), m_FuncName.end());
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

wstring Algorithm::GetName() const
{
    return m_Name;
}

wstring Algorithm::GetDllFileName() const
{
    return m_DllFileName;
}

wstring Algorithm::GetFuncName() const
{
    return m_FuncName;
}

wstring Algorithm::GetIconFileName() const
{
    return m_IconFileName;
}