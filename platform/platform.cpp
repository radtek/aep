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

/**
* @return 平台类的唯一实例.
*
* 用户只能通过该函数获得平台类的唯一实例.
* 若平台类还未被初始化, 则创建唯一的平台类对象,
* 否则直接返回该对象.
*/
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

/**
* @return 结果代码.
*
* 完成平台对象的初始化.
* 首先读取平台配置文件,
* 获得外部组件配置文件名以及算法配置文件名.
* 然后注册所有的外部组件,
* 初始化算法运行环境,
* 注册内部算法.
* 当中任何一个步骤出现错误则直接返回对应的结果代码,
* 全部成功返回OK.
*/
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

/**
* @return 结果代码.
*
* 完成平台对象的销毁.
* 它先释放全部外部组件DLL文件,
* 然后关闭算法运行环境.
* 当中任何一个步骤出现错误则直接返回对应的结果代码,
* 全部成功返回OK.
*/
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

/**
* @return 组件ID的初始值.
*
* 内部算法属于特殊的内部组件.
* 它虽然继承了算法接口,
* 但平台对其会进行特殊的管理,
* 即每个内部算法只有一个实例,
* 不同于其他内部外部组件可以有多个实例.
* 而这些内部算法的实例在平台初始化时即已经构造完毕.
* 他们内部都有一个组件实例ID,
* 在平台外部对外部组件进行建模时,
* 外部组件实例的多少是由用户行为决定的,
* 而这些实例都要有自己的组件实例ID,
* 为了平台能够统一的识别这些ID,
* 需要平台提供外部组件ID的初始值,
* 该值即为当前所有内部算法实例的组件实例ID的最大值加1.
*/
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

/**
* @return 结果代码.
*
* 遍历所有外部组件DLL文件,
* 调用他们的导出函数RegisterInterfaceType完成所有外部接口的注册,
* 再调用他们的导出函数RegisterComponentType完成所有外部组件的注册.
*/
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

/**
* @return 结果代码.
*
* 读取内部算法配置文件,
* 根据配置逐个实例化每个内部算法.
*/
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
