/**
* @file
* @brief �㷨��������cpp�ļ�.
* @author ruoxi
*
* ʵ�����㷨��������.
*/

#include "algorithm_helper.h"
#include "utility.h"
#include "massert.h"

#define RUN_FUNC \
    

LPCSTR AlgorithmHelper::InitializeFuncPrefix = "Initialize";

LPCSTR AlgorithmHelper::FuncPrefix = "mlf";

LPCSTR AlgorithmHelper::TerminateFuncPrefix = "Terminate";

RC AlgorithmHelper::GetParamList(const ParamNameList &paramNameList, ComponentList &componentList, ParamList &paramList)
{
    MASSERT(!paramNameList.empty());
    RC rc;

    for (UINT32 iPl = 0; iPl < paramNameList.size(); ++iPl)
    {
        wstring paramName = paramNameList[iPl];
        bool found = false;
        for (UINT32 iCl = 0; iCl < componentList.size(); ++iCl)
        {
            IComponent *component = componentList[iCl];
            wstring componentName = component->GetName();
            if (paramName == wstring(componentName))
            {
                IParam *param = (IParam *)component->GetInterface(CIID_IPARAM);
                if (NULL != param)
                {
                    paramList.push_back(param);
                    found = true;
                    break;
                }
            }
        }
        if (!found)
        {
            paramList.clear();
            return RC::ALGORITHM_PARAMMISSING_ERROR;
        }
    }

    // FIXME: Check each param size.

    return rc;
}

/**
* @param dllFileName �㷨DLL�ļ���.
* @param funcName �㷨��ں�����.
* @param paramList �㷨�����б�.
* @return �������.
*
* �����㷨DLL�ļ�,
* ����㷨DLL�е������㷨��ʼ���������,
* ��ں�������Լ����������.
* ��˳������㷨��ʼ������, ��ں����Լ�������.
* ����ں����ĵ���, ʹ��������һ���㷨���и�������RealRunFunc.
* �����κ�һ��������ִ�����ֱ�ӷ��ض�Ӧ�Ľ������,
* ȫ���ɹ�����OK.
*/
RC AlgorithmHelper::RunFunc(wstring dllFileName, wstring funcName, ParamList paramList)
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

    Output **output;
    RealRunFunc(algorithmDllHandle, fullFuncName, paramList, output, result);

    if (!result)
    {
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

    terminateFunc();

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

#define GET_REAL_PARAM_LIST \
    vector<Param *> realParamList; \
    for (UINT32 i = 0; i < paramList.size(); ++i) \
    { \
        realParamList.push_back(paramList[i]->ToParam()); \
    }

#define RELEASE_REAL_PARAM_LIST \
    for (UINT32 i = 0; i < paramList.size(); ++i) \
    { \
        ReleaseParam(realParamList[i]); \
    }

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
RC AlgorithmHelper::RealRunFunc(HINSTANCE algorithmDllHandle, string fullFuncName, ParamList paramList, Param **&output, bool &result)
{
    UINT32 paramCount = paramList.size();
    UINT32 paramSize = paramList[0]->GetParamSize();
    switch (paramCount)
    {
    case 1:
        {
            typedef bool (*Func)(int, Param **, Param *);
            GET_FUNC_PROC_ADDR;
            GET_REAL_PARAM_LIST;
            result = func(paramSize, output, realParamList[0]);
            RELEASE_REAL_PARAM_LIST;
            break;
        }
    case 2:
        {
            typedef bool (*Func)(int, Param **, Param *, Param *);
            GET_FUNC_PROC_ADDR;
            GET_REAL_PARAM_LIST;
            result = func(paramSize, output, realParamList[0], realParamList[1]);
            RELEASE_REAL_PARAM_LIST;
            break;
        }
    case 3:
        {
            typedef bool (*Func)(int, Param **, Param *, Param *, Param *);
            GET_FUNC_PROC_ADDR;
            GET_REAL_PARAM_LIST;
            result = func(paramSize, output, realParamList[0], realParamList[1], realParamList[2]);
            RELEASE_REAL_PARAM_LIST;
            break;
        }
    case 4:
        {
            typedef bool (*Func)(int, Param **, Param *, Param *, Param *, Param *);
            GET_FUNC_PROC_ADDR;
            GET_REAL_PARAM_LIST;
            result = func(paramSize, output, realParamList[0], realParamList[1], realParamList[2], realParamList[3]);
            RELEASE_REAL_PARAM_LIST;
            break;
        }
    case 5:
        {
            typedef bool (*Func)(int, Param **, Param *, Param *, Param *, Param *, Param *);
            GET_FUNC_PROC_ADDR;
            GET_REAL_PARAM_LIST;
            result = func(paramSize, output, realParamList[0], realParamList[1], realParamList[2], realParamList[3], realParamList[4]);
            RELEASE_REAL_PARAM_LIST;
            break;
        }
    default:
        return RC::ALGORITHM_OVERMAXPARAMNUM_ERROR;
    }

    return OK;
}

RC AlgorithmHelper::ReleaseParam(Param *param)
{
    RC rc;
    
    // mxDestroyArray(param);
    delete param;

    return rc;
}
