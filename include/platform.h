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

public:
    ComponentInfoList &GetComponentInfoList();
    ComponentList &GetComponentList();

    AlgorithmList &GetAlgorithmList();

private:
    // ƽ̨��������
    RC LoadComponentDll();
    RC RegisterComponentInfo();
    RC RegisterGetComponentListFuncToComponent();
    RC UnloadComponentDll();

    RC InitAlgorithm();
    RC ShutAlgorithm();
    /** @brief �������ļ����õ��㷨�б�. */
    RC RegisterAlgorithm();
    /** @brief ��һ���㷨��ӵ������ļ���. */
    RC AddAlgorithm();

private:
    ComponentInfoList m_ComponentInfoList;
    ComponentList m_ComponentList;

    AlgorithmList m_AlgorithmList;

    HINSTANCE m_ComponentDllHandle;

private:
    LPCWSTR m_ComponentDllFileName;
    LPCWSTR m_AlgorithmCfgFileName;

public:
    static Platform &GetInstance();

private:
    Platform();
    static Platform *s_Instance;
    static bool s_Initialized;

    static LPCSTR s_CfgFileName;
    static LPCSTR s_ComponentDllFileNameKey;
    static LPCSTR s_AlgorithmCfgFileNameKey;
};

#endif // __PLATFORM_H__
