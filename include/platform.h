/**
* @file
* @brief ƽ̨ͷ�ļ�.
* @author ruoxi
*
* ������ƽ̨��.
*/

// FIXME: ����ƽ̨���Ƽ�ͼ���Ҫ��.

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "interfaces.h"
#include "algorithm.h"

class Platform
{
public:
    // ƽ̨��ʼ�����ر�
    RC Init();
    RC Shut();

public:
    // ƽ̨����
    RC ValidateModel(bool &result);
    RC RunModel();
    RC RunAlgorithm(const AlgorithmInfo &algorithmInfo);

public:
    ComponentInfoList &GetComponentInfoList();
    ComponentList &GetComponentList();

    AlgorithmInfoList &GetAlgorithmInfoList();

private:
    // ƽ̨��������
    RC LoadComponentDll();
    RC RegisterComponentInfo();
    RC RegisterGetComponentListFuncToComponent();
    RC UnloadComponentDll();

    RC InitAlgorithm();
    RC RegisterAlgorithm();
    RC ShutAlgorithm();

private:
    ComponentInfoList m_ComponentInfoList;
    ComponentList m_ComponentList;

    AlgorithmInfoList m_AlgorithmInfoList;

    HINSTANCE m_ComponentDllHandle;
    HINSTANCE m_AlgorithmDllHandle;

private:
    LPCWSTR m_ComponentDllFileName;
    LPCWSTR m_AlgorithmCfgFileName;

public:
    static Platform &GetInstance();

private:
    Platform();
    static Platform *s_Instance;
    static bool s_Initialized;

    static LPCWSTR s_CfgFileName;
};

#endif // __PLATFORM_H__
