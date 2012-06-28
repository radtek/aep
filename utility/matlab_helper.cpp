/**
* @file
* @brief MatLab��������cpp�ļ�.
* @author ruoxi
*
* ʵ����MatLab��������.
*/

#include "matlab_helper.h"

#include "utility.h"

LPCSTR MatLabHelper::InitializeFuncPrefix = "Initialize";

LPCSTR MatLabHelper::FuncPrefix = "mlx";
//LPCSTR MatLabHelper::FuncPrefix = "mlf";

LPCSTR MatLabHelper::PrintStackFuncPrefix = "PrintStackTrace";

LPCSTR MatLabHelper::TerminateFuncPrefix = "Terminate";

Array *MatLabHelper::CreateDoubleArray(UINT32 x, UINT32 y,
                                       const char *content,
                                       UINT32 width, UINT32 height,
                                       UINT32 startX, UINT32 startY)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    double *p = mxGetPr(a);
    memset(p, 0, x * y * sizeof(double));
    if (content)
    {
        if (width && height)
        {
            for (UINT32 yy = 0; yy < min(y, height - startY); ++yy)
            {
                for (UINT32 xx = 0; xx < min(x, width - startX); ++xx)
                {
                    p[yy * x + xx] = content[(startY + yy) * width + startX + xx];
                }
            }
        }
        else
        {
            for (UINT32 i = 0; i < x * y; ++i)
            {
                p[i] = content[i];
            }
        }
    }

    return a;
}

Array *MatLabHelper::CreateDoubleArray(UINT32 x, UINT32 y,
                                       const double *content,
                                       UINT32 width, UINT32 height,
                                       UINT32 startX, UINT32 startY)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    double *p = mxGetPr(a);
    memset(p, 0, x * y * sizeof(double));
    if (content)
    {
        if (width && height)
        {
            for (UINT32 yy = 0; yy < min(y, height - startY); ++yy)
            {
                for (UINT32 xx = 0; xx < min(x, width - startX); ++xx)
                {
                    p[yy * x + xx] = content[(startY + yy) * width + startX + xx];
                }
            }
        }
        else
        {
            for (UINT32 i = 0; i < x * y; ++i)
            {
                p[i] = content[i];
            }
        }
    }

    return a;
}

Array *MatLabHelper::CreateDoubleArray(UINT32 x, UINT32 y,
                                       const char *content,
                                       UINT32 size, UINT32 start)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    double *p = mxGetPr(a);
    memset(p, 0, x * y * sizeof(double));
    if (content)
    {
        if (size)
        {
            for (UINT32 i = 0; i < min(x * y, size - start); ++i)
            {
                p[i] = content[start + i];
            }
        }
        else
        {
            for (UINT32 i = 0; i < x * y; ++i)
            {
                p[i] = content[i];
            }
        }
    }

    return a;
}

Array *MatLabHelper::CreateDoubleArray(UINT32 x, UINT32 y,
                                       const double *content,
                                       UINT32 size, UINT32 start)
{
    Array *a = mxCreateDoubleMatrix(x, y, mxREAL);

    double *p = mxGetPr(a);
    memset(p, 0, x * y * sizeof(double));
    if (content)
    {
        if (size)
        {
            for (UINT32 i = 0; i < min(x * y, size - start); ++i)
            {
                p[i] = content[start + i];
            }
        }
        else
        {
            for (UINT32 i = 0; i < x * y; ++i)
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

RC MatLabHelper::RunFunc(wstring dllFileName, wstring funcName, vector<Array *> &outputList, vector<Array *> &inputList)
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
* @param algorithmDllHandle �㷨DLL�ļ����.
* @param fullFuncName �㷨��ں���ȫ��.
* @param paramList �㷨�����б�.
* @param output �㷨���.
* @param result �㷨���ý��.
* @return �������.
*
* �ú������㷨���и�����������,
* ����ʵ�ֶ�һ���㷨��ں����ľ������.
* �ú��������㷨DLL�ļ�����Լ��㷨��ں���ȫ��(ͨ��MatLab�����ĺ��������ǰ׺),
* ���տɱ�����Ĳ���,
* �Բ����������б���,
* ʵ�ֶԲ����б��޲�����(Ŀǰ���֧��5������, ������Ҫ����������),
* ���Ҽ�¼�㷨���ý��.
*/
RC MatLabHelper::RealRunFunc(HINSTANCE algorithmDllHandle, string fullFuncName, vector<Array *> &outputList, vector<Array *> &inputList, bool &result)
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
    /*
    switch (outputCount)
    {
    case 1:
        {
            SWITCH_INPUT_COUNT(outputList[0])
            break;
        }
    case 2:
        {
            SWITCH_INPUT_COUNT(outputList[0], outputList[1])
            break;
        }
    case 3:
        {
            SWITCH_INPUT_COUNT(outputList[0], outputList[1], outputList[2])
            break;
        }
    case 4:
        {
            SWITCH_INPUT_COUNT(outputList[0], outputList[1], outputList[2], outputList[3])
            break;
        }
    case 5:
        {
            SWITCH_INPUT_COUNT(outputList[0], outputList[1], outputList[2], outputList[3], outputList[4])
            break;
        }
    default:
        return RC::ALGORITHM_OVERMAXOUTPUT_ERROR;
    }
    */

    return OK;
}
