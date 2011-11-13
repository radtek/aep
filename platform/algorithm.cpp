/**
* @file
* @brief 算法相关函数cpp文件.
* @author ruoxi
*
* 实现了算法相关函数.
*/

#include "algorithm.h"
#include "algorithm_helper.h"
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

Algorithm::Algorithm(wstring name,
                     wstring dllFileName,
                     wstring funcName,
                     wstring iconFileName,
                     ParamNameList paramNameList)
:
m_Name(name),
m_DllFileName(dllFileName),
m_FuncName(funcName),
m_IconFileName(iconFileName),
m_ParamNameList(paramNameList)
{
}

RC Algorithm::Run(ComponentList &componentList)
{
    RC rc;

    ParamList paramList;
    CHECK_RC(AlgorithmHelper::GetParamList(m_ParamNameList, componentList, paramList));
    CHECK_RC(AlgorithmHelper::RunFunc(m_DllFileName, m_FuncName, paramList));

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