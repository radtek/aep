/**
* @file
* @brief 算法辅助函数cpp文件.
* @author ruoxi
*
* 实现了算法辅助函数.
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
* @param dllFileName 算法DLL文件名.
* @param funcName 算法入口函数名.
* @param paramList 算法参数列表.
* @return 结果代码.
*
* 加载算法DLL文件,
* 获得算法DLL中导出的算法初始化函数句柄,
* 入口函数句柄以及清理函数句柄.
* 按顺序调用算法初始化函数, 入口函数以及清理函数.
* 对入口函数的调用, 使用了另外一个算法运行辅助函数RealRunFunc.
* 当中任何一个步骤出现错误则直接返回对应的结果代码,
* 全部成功返回OK.
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
