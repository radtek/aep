/**
* @file
* @brief �㷨��غ���cpp�ļ�.
* @author ruoxi
*
* ʵ�����㷨��غ���.
*/

#include "stdafx.h"

#include "algorithm.h"

RC Algorithm::Init()
{
    RC rc;
    // mclInitializeApplication(NULL, 0); //��ʼ��MATLAB API�ӿ�
    // mclTerminateApplication(); //�ر�MATLAB API�ӿ�
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
    // mclInitializeApplication(NULL, 0); //��ʼ��MATLAB API�ӿ�
    // mclTerminateApplication(); //�ر�MATLAB API�ӿ�
    return rc;
}

LPCWSTR Algorithm::AlgorithmListFileName = TEXT("algorithm_list.ini");