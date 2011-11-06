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
    RC RunAlgorithm(const AlgorithmInfo &algorithmInfo);

public:
    ComponentInfoList &GetComponentInfoList();
    ComponentList &GetComponentList();

    AlgorithmInfoList &GetAlgorithmInfoList();

private:
    // 平台辅助函数
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
