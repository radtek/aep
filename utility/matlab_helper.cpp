/**
* @file
* @brief MatLab辅助函数cpp文件.
* @author ruoxi
*
* 实现了MatLab辅助函数.
*/

#include "matlab_helper.h"

#include "utility.h"

LPCSTR MatLabHelper::InitializeFuncPrefix = "Initialize";

LPCSTR MatLabHelper::FuncPrefix = "mlf";

LPCSTR MatLabHelper::PrintStackFuncPrefix = "PrintStackTrace";

LPCSTR MatLabHelper::TerminateFuncPrefix = "Terminate";

Array *MatLabHelper::CreateDoubleArray(UINT32 x, UINT32 y, const char *content, UINT32 size)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    if (content)
    {
        double *p = mxGetPr(a);
        if (size)
        {
            size = min(size, x * y);
        }
        for (UINT32 i = 0; i < size; ++i)
        {
            p[i] = content[i];
        }
    }

    return a;
}

Array *MatLabHelper::CreateDoubleArray(UINT32 x, UINT32 y, const double *content, UINT32 size)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    if (content)
    {
        double *p = mxGetPr(a);
        if (size)
        {
            size = min(size, x * y);
        }
        for (UINT32 i = 0; i < size; ++i)
        {
            p[i] = content[i];
        }
    }

    return a;
}

void MatLabHelper::DestroyArray(Array *a)
{
    mxDestroyArray(a);
}

RC MatLabHelper::RunFunc(wstring dllFileName, wstring funcName, UINT32 outputCount, Array **output, const vector<Array *> &inputList)
{
    RC rc;

    HINSTANCE algorithmDllHandle = LoadLibrary(dllFileName.c_str());

    if (!algorithmDllHandle)
    {
        Utility::PromptLastErrorMessage();
        return RC::ALGORITHM_LOADDLL_ERROR;
    }

    bool result;
    string sFuncName(funcName.begin(), funcName.end());

    string initializeFuncName = sFuncName;
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

    string fullFuncName = FuncPrefix;
    fullFuncName += sFuncName;

    CHECK_RC(RealRunFunc(algorithmDllHandle, fullFuncName, outputCount, output, inputList, result));

    if (!result)
    {
        string printStackFuncName = sFuncName;
        printStackFuncName += PrintStackFuncPrefix;

        PrintStackFunc printStackFunc = (PrintStackFunc)GetProcAddress(
            (HMODULE)algorithmDllHandle,
            printStackFuncName.c_str());

        printStackFunc();

        return RC::ALGORITHM_RUN_ERROR;
    }

    string terminateFuncName = sFuncName;
    terminateFuncName += TerminateFuncPrefix;

    TerminateFunc terminateFunc = (TerminateFunc)GetProcAddress(
        (HMODULE)algorithmDllHandle,
        terminateFuncName.c_str());

    if (!terminateFunc)
    {
        Utility::PromptLastErrorMessage();
        return RC::ALGORITHM_GETPROC_ERROR;
    }

    // terminateFunc();

    return rc;
}

#define GET_FUNC_PROC_ADDR \
    Func func = (Func)GetProcAddress( \
        algorithmDllHandle, \
        fullFuncName.c_str()); \
    if (!func) \
    { \
        Utility::PromptLastErrorMessage(); \
        return RC::ALGORITHM_GETPROC_ERROR; \
    } \

/**
* @param algorithmDllHandle 算法DLL文件句柄.
* @param fullFuncName 算法入口函数全名.
* @param paramList 算法参数列表.
* @param output 算法输出.
* @param result 算法调用结果.
* @return 结果代码.
*
* 该函数被算法运行辅助函数调用,
* 用来实现对一个算法入口函数的具体调用.
* 该函数接收算法DLL文件句柄以及算法入口函数全名(通常MatLab导出的函数会添加前缀),
* 接收可变个数的参数,
* 对参数个数进行遍历,
* 实现对参数列表无差别调用(目前最大支持5个参数, 如有需要可随意增加),
* 并且记录算法调用结果.
*/
RC MatLabHelper::RealRunFunc(HINSTANCE algorithmDllHandle, string fullFuncName, UINT32 outputCount, Array **output, const vector<Array *> &inputList, bool &result)
{
    UINT32 inputCount = inputList.size();
    switch (inputCount)
    {
    case 1:
        {
            typedef bool (*Func)(int, Array **, Array *);
            GET_FUNC_PROC_ADDR;
            result = func(outputCount, output, inputList[0]);
            break;
        }
    case 2:
        {
            typedef bool (*Func)(int, Array **, Array *, Array *);
            GET_FUNC_PROC_ADDR;
            result = func(outputCount, output, inputList[0], inputList[1]);
            break;
        }
    default:
        return RC::ALGORITHM_OVERMAXPARAMNUM_ERROR;
    }

    return OK;
}
