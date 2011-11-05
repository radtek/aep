/**
* @file
* @brief 算法相关函数cpp文件.
* @author ruoxi
*
* 实现了算法相关函数.
*/

#include "stdafx.h"

#include "algorithm.h"

RC Algorithm::Init()
{
    RC rc;
    // mclInitializeApplication(NULL, 0); //初始化MATLAB API接口
    // mclTerminateApplication(); //关闭MATLAB API接口
    return rc;
}

RC Algorithm::RegisterAlgorithm(AlgorithmInfoList &algorithmInfoList)
{
    RC rc;
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
    // mclInitializeApplication(NULL, 0); //初始化MATLAB API接口
    // mclTerminateApplication(); //关闭MATLAB API接口
    return rc;
}

LPCWSTR Algorithm::AlgorithmListFileName = TEXT("algorithm_list.ini");