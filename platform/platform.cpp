/**
* @file
* @brief 平台cpp文件.
* @author ruoxi
*
* 实现了平台类.
*/

#include "platform.h"
#include "component.h"
#include "config_file.h"
#include "algorithm_data_file.h"
#include "component_type_data_file.h"

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
LPCWSTR Platform::s_ComponentDllFileNameKey = TEXT("COMPONENT_DLL_FILE_NAME");
LPCWSTR Platform::s_ComponentCfgFileNameKey = TEXT("COMPONENT_CFG_FILE_NAME");
LPCWSTR Platform::s_AlgorithmCfgFileNameKey = TEXT("ALGORITHM_CFG_FILE_NAME");

void GetComponentList(ComponentList &componentList)
{
    componentList = Platform::GetInstance().GetComponentList();
}

RC Platform::Init()
{
    RC rc;

    ConfigFile configFile(s_CfgFileName);
    m_ComponentCfgFileName = configFile.read<wstring>(s_ComponentCfgFileNameKey);
    m_AlgorithmCfgFileName = configFile.read<wstring>(s_AlgorithmCfgFileNameKey);

    // CHECK_RC(LoadComponentDll());
    // CHECK_RC(RegisterInterfaceType());
    CHECK_RC(RegisterComponentType());
    // CHECK_RC(RegisterGetComponentListFuncToComponent());

    CHECK_RC(InitAlgorithm());
    // CHECK_RC(RegisterAlgorithm());
    CHECK_RC(RegisterInternalAlgorithm());

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
/*
    Component::ValidateModelFunc func =
        (Component::ValidateModelFunc)GetProcAddress(
        (HMODULE)m_ComponentDllHandle,
        Component::ValidateModelFuncName);

    if (!func)
    {
        return RC::PLATFORM_VALIDATEMODEL_ERROR;
    }

    result = func();
*/
    return rc;
}

RC Platform::RunModel()
{
    RC rc;
/*
    Component::RunModelFunc func =
        (Component::RunModelFunc)GetProcAddress(
        (HMODULE)m_ComponentDllHandle,
        Component::RunModelFuncName);

    if (!func)
    {
        return RC::PLATFORM_RUNMODEL_ERROR;
    }

    func();
*/
    return rc;
}

InterfaceTypeMap &Platform::GetInterfaceTypeMap()
{
    return m_InterfaceTypeMap;
}

ComponentTypeMap &Platform::GetComponentTypeMap()
{
    return m_ComponentTypeMap;
}

ComponentList &Platform::GetComponentList()
{
    return m_ComponentList;
}

AlgorithmList &Platform::GetAlgorithmList()
{
    return m_AlgorithmList;
}

InternalAlgorithmMap &Platform::GetInternalAlgorithmMap()
{
    return m_InternalAlgorithmMap;
}

UINT32 Platform::GetComponentIdStart()
{
    UINT32 idStart = 0;

    for (InternalAlgorithmMap::iterator it = m_InternalAlgorithmMap.begin();
        it != m_InternalAlgorithmMap.end(); ++it)
    {
        InternalAlgorithm &internalAlgorithm = it->second;
        if (internalAlgorithm.GetId() >= idStart)
        {
            idStart = internalAlgorithm.GetId() + 1;
        }
    }

    return idStart;
}

RC Platform::LoadComponentDll()
{
    RC rc;

    m_ComponentDllHandle = LoadLibrary(m_ComponentDllFileName.c_str());

    if (!m_ComponentDllHandle)
    {
        return RC::PLATFORM_LOADDLL_ERROR;
    }

    return rc;
}

RC Platform::RegisterInterfaceType()
{
    RC rc;

    return rc;
}

RC Platform::RegisterComponentType()
{
    RC rc;

    ComponentTypeDataFile file(m_ComponentCfgFileName);
    file.Parse();
    m_InterfaceTypeMap = file.GetInterfaceTypeMap();
    m_ComponentTypeMap = file.GetComponentTypeMap();

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

    if (!FreeLibrary((HMODULE)m_ComponentDllHandle))
    {
        return RC::PLATFORM_UNLOADDLL_ERROR;
    }

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

    // Algorithm algorithm(TEXT("加法"), TEXT("AddFunc.dll"), TEXT("AddFunc"), TEXT("AddFunc.ico"));
    // m_AlgorithmList.push_back(algorithm);
    // file.InsertAlgorithm(algorithm);

    AlgorithmDataFile file(m_AlgorithmCfgFileName);
    file.Parse();
    m_AlgorithmList = file.GetAlgorithmList();

    return rc;
}

RC Platform::RegisterInternalAlgorithm()
{
    RC rc;

    // Algorithm algorithm(TEXT("加法"), TEXT("AddFunc.dll"), TEXT("AddFunc"), TEXT("AddFunc.ico"));
    // m_AlgorithmList.push_back(algorithm);
    // file.InsertAlgorithm(algorithm);

    AlgorithmDataFile file(m_AlgorithmCfgFileName);
    file.Parse();
    m_InternalAlgorithmMap = file.GetInternalAlgorithmMap();

    return rc;
}

RC Platform::UploadAlgorithm()
{
    RC rc;
    // FIXME
    return rc;
}
