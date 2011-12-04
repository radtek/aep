/**
* @file
* @brief 平台头文件.
* @author ruoxi
*
* 定义了平台类.
*/

// FIXME: 加入平台名称及图表等要素.

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "interfaces.h"
#include "algorithm.h"

class Platform
{
public:
    // 平台初始化及关闭
    RC Init();
    RC Shut();

public:
    // 平台功能
    RC ValidateModel(bool &result);
    RC RunModel();

public:
    InterfaceTypeMap &GetInterfaceTypeMap();

    ComponentTypeMap &GetComponentTypeMap();
    ComponentList &GetComponentList();

    AlgorithmList &GetAlgorithmList();

private:
    // 平台辅助函数
    RC LoadComponentDll();
    RC RegisterInterfaceType();
    RC RegisterComponentType();
    RC RegisterGetComponentListFuncToComponent();
    RC UnloadComponentDll();

    RC InitAlgorithm();
    RC ShutAlgorithm();
    /** @brief 从配置文件中拿到算法列表. */
    RC RegisterAlgorithm();
    /** @brief 将一个算法添加到配置文件中. */
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
