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
