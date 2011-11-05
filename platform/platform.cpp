/**
* @file
* @brief 平台cpp文件.
* @author ruoxi
*
* 实现了平台类.
*/

#include "stdafx.h"

#include "platform.h"
#include "component.h"

Platform &Platform::GetInstance()
{
    if (!s_Initialized)
    {
        s_Instance = new Platform;
        s_Initialized = true;
    }
    return *s_Instance;
}

Platform::Platform()
{
}

Platform *Platform::s_Instance = NULL;

bool Platform::s_Initialized = false;

void GetComponentList(ComponentList &componentList)
{
    componentList = Platform::GetInstance().GetComponentList();
}

RC Platform::LoadComponentDll(LPCWSTR fileName)
{
    m_ComponentDllHandle = LoadLibrary(fileName);

    if (!m_ComponentDllHandle)
    {
        return RC::PLATFORM_LOADDLL_ERROR;
    }

    return OK;
}

RC Platform::LoadAlgorithmDll(LPCWSTR fileName)
{
    m_AlgorithmDllHandle = LoadLibrary(fileName);

    if (!m_AlgorithmDllHandle)
    {
        return RC::PLATFORM_LOADDLL_ERROR;
    }

    return OK;
}

RC Platform::RegisterComponentInfo()
{
    RC rc;

    Component::RegisterComponentInfoFunc func =
        (Component::RegisterComponentInfoFunc)GetProcAddress(
        (HMODULE)m_ComponentDllHandle,
        Component::RegisterComponentInfoFuncName);

    if (!func)
    {
        return RC::PLATFORM_REGISTERCOMPONENTINFO_ERROR;
    }

    func(m_ComponentInfoList);

    return rc;
}

RC Platform::RegisterAlgorithm()
{
    RC rc;

    // 读algorithm.ini文件, 获得算法列表

    return rc;
}

/*
RC Platform::RegisterAlgorithm()
{
    RC rc;

    Component::RegisterAlgorithmFunc func =
        (Component::RegisterAlgorithmFunc)GetProcAddress(
        (HMODULE)m_AlgorithmDllHandle,
        Component::RegisterAlgorithmFuncName);

    if (!func)
    {
        return RC::PLATFORM_REGISTERALGORITHM_ERROR;
    }

    func(m_AlgorithmList);

    return rc;
}
*/

RC Platform::RegisterGetComponentListFuncToComponent()
{
    RC rc;

    Component::RegisterGetComponentListFuncFunc func =
        (Component::RegisterGetComponentListFuncFunc)GetProcAddress(
        (HMODULE)m_ComponentDllHandle,
        Component::RegisterGetComponentListFuncFuncName);

    if (!func)
    {
        return RC::PLATFORM_REGISTERGETCOMPONENTLISTFUNC_ERROR;
    }

    func((Component::GetComponentListFunc)::GetComponentList);

    return rc;
}

RC Platform::RegisterGetComponentListFuncToAlgorithm()
{
    RC rc;

    Component::RegisterGetComponentListFuncFunc func =
        (Component::RegisterGetComponentListFuncFunc)GetProcAddress(
        (HMODULE)m_AlgorithmDllHandle,
        Component::RegisterGetComponentListFuncFuncName);

    if (!func)
    {
        return RC::PLATFORM_REGISTERGETCOMPONENTLISTFUNC_ERROR;
    }

    func((Component::GetComponentListFunc)::GetComponentList);

    return rc;
}

RC Platform::ValidateModel(bool &result)
{
    RC rc;

    Component::ValidateModelFunc func =
        (Component::ValidateModelFunc)GetProcAddress(
        (HMODULE)m_ComponentDllHandle,
        Component::ValidateModelFuncName);

    if (!func)
    {
        return RC::PLATFORM_VALIDATEMODEL_ERROR;
    }

    result = func();

    return rc;
}

RC Platform::RunModel()
{
    RC rc;

    Component::RunModelFunc func =
        (Component::RunModelFunc)GetProcAddress(
        (HMODULE)m_ComponentDllHandle,
        Component::RunModelFuncName);

    if (!func)
    {
        return RC::PLATFORM_RUNMODEL_ERROR;
    }

    func();

    return rc;
}

RC Platform::UnloadComponentDll()
{
    FreeLibrary((HMODULE)m_ComponentDllHandle);
    return OK;
}

RC Platform::UnloadAlgorithmDll()
{
    FreeLibrary((HMODULE)m_AlgorithmDllHandle);
    return OK;
}

ComponentInfoList &Platform::GetComponentInfoList()
{
    return m_ComponentInfoList;
}

ComponentList &Platform::GetComponentList()
{
    return m_ComponentList;
}

AlgorithmList &Platform::GetAlgorithmList()
{
    return m_AlgorithmList;
}
