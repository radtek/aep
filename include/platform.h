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
    InterfaceTypeMap &GetInterfaceTypeMap();

    ComponentTypeMap &GetComponentTypeMap();
    ComponentList &GetComponentList();

    AlgorithmList &GetAlgorithmList();

private:
    // ƽ̨��������
    RC LoadComponentDll();
    RC RegisterInterfaceType();
    RC RegisterComponentType();
    RC RegisterGetComponentListFuncToComponent();
    RC UnloadComponentDll();

    RC InitAlgorithm();
    RC ShutAlgorithm();
    /** @brief �������ļ����õ��㷨�б�. */
    RC RegisterAlgorithm();
    /** @brief ��һ���㷨��ӵ������ļ���. */
    RC UploadAlgorithm();

private:
    InterfaceTypeMap m_InterfaceTypeMap;

    ComponentTypeMap m_ComponentTypeMap;
    ComponentList m_ComponentList;

    AlgorithmList m_AlgorithmList;

    HINSTANCE m_ComponentDllHandle;

private:
    wstring m_ComponentDllFileName;
    wstring m_AlgorithmCfgFileName;

public:
    static Platform &GetInstance();

private:
    Platform();
    static Platform *s_Instance;
    static bool s_Initialized;

    static LPCWSTR s_CfgFileName;
    static LPCWSTR s_ComponentDllFileNameKey;
    static LPCWSTR s_AlgorithmCfgFileNameKey;
};

#endif // __PLATFORM_H__
