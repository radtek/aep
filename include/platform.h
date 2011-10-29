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

class Platform
{
public:
    RC LoadComponentDll(LPCWSTR fileName);
    RC LoadAlgorithmDll(LPCWSTR fileName);
    RC RegisterComponentInfo();
    RC RegisterAlgorithm();
    RC RegisterGetComponentListFuncToComponent();
    RC RegisterGetComponentListFuncToAlgorithm();
    RC ValidateModel(bool &result);
    RC RunModel();
    RC UnloadComponentDll();
    RC UnloadAlgorithmDll();

    ComponentInfoList &GetComponentInfoList();
    ComponentList &GetComponentList();

    AlgorithmList &GetAlgorithmList();

private:
    ComponentInfoList m_ComponentInfoList;
    ComponentList m_ComponentList;

    AlgorithmList m_AlgorithmList;

    HINSTANCE m_ComponentDllHandle;
    HINSTANCE m_AlgorithmDllHandle;

public:
    static Platform &GetInstance();

private:
    Platform();
    static Platform *s_Instance;
    static bool s_Initialized;
};

#endif // __PLATFORM_H__
