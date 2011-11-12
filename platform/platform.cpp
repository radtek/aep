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

LPCWSTR Platform::s_CfgFileName = TEXT("platform.cfg");

void GetComponentList(ComponentList &componentList)
{
    componentList = Platform::GetInstance().GetComponentList();
}

RC Platform::Init()
{
    RC rc;

    // FIXME: Load from cfg.
    m_ComponentDllFileName = TEXT("aircraft_measure.dll");
    m_AlgorithmCfgFileName = TEXT("aircraft_measure_algorithm.cfg");

    CHECK_RC(LoadComponentDll());
    CHECK_RC(RegisterComponentInfo());
    CHECK_RC(RegisterGetComponentListFuncToComponent());

    CHECK_RC(InitAlgorithm());
    CHECK_RC(RegisterAlgorithm());

    return rc;
}

RC Platform::Shut()
{
    RC rc;

    CHECK_RC(UnloadComponentDll());

    CHECK_RC(ShutAlgorithm());

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

RC Platform::LoadComponentDll()
{
    RC rc;

    m_ComponentDllHandle = LoadLibrary(m_ComponentDllFileName);

    if (!m_ComponentDllHandle)
    {
        return RC::PLATFORM_LOADDLL_ERROR;
    }

    return rc;
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

RC Platform::UnloadComponentDll()
{
    RC rc;

    // FIXME.
    FreeLibrary((HMODULE)m_ComponentDllHandle);

    return rc;
}

RC Platform::InitAlgorithm()
{
    RC rc;

    CHECK_RC(Algorithm::Init());

    return rc;
}

RC Platform::ShutAlgorithm()
{
    RC rc;

    CHECK_RC(Algorithm::Shut());

    return rc;
}

RC Platform::RegisterAlgorithm()
{
    RC rc;

    // FIXME: Load from cfg file.
    Algorithm algorithm(TEXT("加法"), TEXT("AddFunc.dll"), "AddFunc", TEXT("AddFunc.ico"));
    m_AlgorithmList.push_back(algorithm);

    return rc;
}

RC Platform::AddAlgorithm()
{
    RC rc;
    // FIXME
    return rc;
}
