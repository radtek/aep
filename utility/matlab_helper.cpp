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

LPCSTR MatLabHelper::FuncPrefix = "mlx";
//LPCSTR MatLabHelper::FuncPrefix = "mlf";

LPCSTR MatLabHelper::PrintStackFuncPrefix = "PrintStackTrace";

LPCSTR MatLabHelper::TerminateFuncPrefix = "Terminate";

Array *MatLabHelper::CreateDoubleArray(INT32 x, INT32 y,
                                       const unsigned char *content,
                                       INT32 width, INT32 height,
                                       INT32 startX, INT32 startY)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    double *p = mxGetPr(a);
    memset(p, 0, x * y * sizeof(double));
    if (content)
    {
        if (width && height)
        {
            for (INT32 yy = max(0, -startY); yy < min(y, height - startY); ++yy)
            {
                for (INT32 xx = max(0, -startX); xx < min(x, width - startX); ++xx)
                {
                    p[yy * x + xx] = content[(startY + yy) * width + startX + xx];
                }
            }
        }
        else
        {
            for (INT32 i = 0; i < x * y; ++i)
            {
                p[i] = content[i];
            }
        }
    }

    return a;
}

Array *MatLabHelper::CreateDoubleArray(INT32 x, INT32 y,
                                       const double *content,
                                       INT32 width, INT32 height,
                                       INT32 startX, INT32 startY)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    double *p = mxGetPr(a);
    memset(p, 0, x * y * sizeof(double));
    if (content)
    {
        if (width && height)
        {
            for (INT32 yy = max(0, -startY); yy < min(y, height - startY); ++yy)
            {
                for (INT32 xx = max(0, -startX); xx < min(x, width - startX); ++xx)
                {
                    p[yy * x + xx] = content[(startY + yy) * width + startX + xx];
                }
            }
        }
        else
        {
            for (INT32 i = 0; i < x * y; ++i)
            {
                p[i] = content[i];
            }
        }
    }

    return a;
}

Array *MatLabHelper::CreateDoubleArray(INT32 x, INT32 y,
                                       const unsigned char *content,
                                       INT32 size, INT32 start)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    double *p = mxGetPr(a);
    memset(p, 0, x * y * sizeof(double));
    if (content)
    {
        if (size)
        {
            for (INT32 i = max(0, -start); i < min(x * y, size - start); ++i)
            {
                p[i] = content[start + i];
            }
        }
        else
        {
            for (INT32 i = 0; i < x * y; ++i)
            {
                p[i] = content[i];
            }
        }
    }

    return a;
}

Array *MatLabHelper::CreateDoubleArray(INT32 x, INT32 y,
                                       const double *content,
                                       INT32 size, INT32 start)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    double *p = mxGetPr(a);
    memset(p, 0, x * y * sizeof(double));
    if (content)
    {
        if (size)
        {
            for (INT32 i = max(0, -start); i < min(x * y, size - start); ++i)
            {
                p[i] = content[start + i];
            }
        }
        else
        {
            for (INT32 i = 0; i < x * y; ++i)
            {
                p[i] = content[i];
            }
        }
    }

    return a;
}

void MatLabHelper::DestroyArray(Array *a)
{
    mxDestroyArray(a);
}

RC MatLabHelper::RunFunc(const wstring &dllFileName, const wstring &funcName, vector<Array *> &outputList, vector<Array *> &inputList)
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

    string fullFuncName = sFuncName;
    fullFuncName[0] = toupper(fullFuncName[0]);
    fullFuncName = FuncPrefix + fullFuncName;

    CHECK_RC(RealRunFunc(algorithmDllHandle, fullFuncName, outputList, inputList, result));

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

/*
#define SWITCH_INPUT_COUNT(...) \
    switch (inputCount) \
    { \
    case 1: \
        {
            typedef bool (*Func)(int, Array **, Array *); \
            GET_FUNC_PROC_ADDR; \
            result = func(outputCount, __VA_ARGS__, inputList[0]); \
            break; \
        } \
    case 2: \
        { \
            typedef bool (*Func)(int, Array **, Array *, Array *); \
            GET_FUNC_PROC_ADDR; \
            result = func(outputCount, __VA_ARGS__, inputList[0], inputList[1]); \
            break; \
        } \
    default: \
        return RC::ALGORITHM_OVERMAXPARAMNUM_ERROR; \
    } \
    */

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
RC MatLabHelper::RealRunFunc(HINSTANCE algorithmDllHandle, const string &fullFuncName, vector<Array *> &outputList, vector<Array *> &inputList, bool &result)
{
    UINT32 outputCount = outputList.size();
    UINT32 inputCount = inputList.size();

    typedef bool (*Func)(int, Array *[], int, Array *[]);
    Func func = (Func)GetProcAddress(
        algorithmDllHandle,
        fullFuncName.c_str());
    if (!func)
    {
        Utility::PromptLastErrorMessage();
        return RC::ALGORITHM_GETPROC_ERROR;
    }
    result = func(outputCount, &outputList[0], inputCount, &inputList[0]);

    return OK;
}
