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
#include "internal_algorithm.h"

/**
* @class Platform
* @brief Platform平台类.
*
* Platform平台类抽象出了平台的全部操作,
* 包括初始化, 关闭, 管理接口, 组件, 算法等等.
* 该类的设计采用了单态模式(singleton), 在代码层面保证了它只能有一个实例.
*/
class Platform
{
public:
    // 平台初始化及关闭
    /** @brief 平台初始化. */
    RC Init();
    /** @brief 平台关闭. */
    RC Shut();

public:
    // 平台功能
    RC ValidateModel(bool &result);
    RC RunModel();

public:
    /** @brief 获得外部接口类型列表. */
    InterfaceTypeMap &GetInterfaceTypeMap();

    /** @brief 获得组件类型列表. */
    ComponentTypeMap &GetComponentTypeMap();
    /** @brief 获得组件实例列表. */
    ComponentList &GetComponentList();

    /** @brief 获得算法列表. */
    AlgorithmList &GetAlgorithmList();

    /** @brief 获得内部算法列表. */
    InternalAlgorithmMap &GetInternalAlgorithmMap();

    /** @brief 获得组件ID起始值. */
    UINT32 GetComponentIdStart();

private:
    // 平台辅助函数
    RC LoadComponentDll();
    RC RegisterInterfaceType();
    /** @brief 注册所有组件类型. */
    RC RegisterComponentType();
    RC RegisterGetComponentListFuncToComponent();
    /** @brief 释放外部组件DLL文件. */
    RC UnloadComponentDll();

    /** @brief 初始化算法运行环境. */
    RC InitAlgorithm();
    /** @brief 关闭算法运行环境. */
    RC ShutAlgorithm();
    RC RegisterAlgorithm();

    /** @brief 注册内部算法. */
    RC RegisterInternalAlgorithm();
    RC UploadAlgorithm();

private:
    /** @brief 外部接口类型列表. */
    InterfaceTypeMap m_InterfaceTypeMap;

    /** @brief 外部组件类型列表. */
    ComponentTypeMap m_ComponentTypeMap;
    /** @brief 组件实例列表. */
    ComponentList m_ComponentList;

    /** @brief 算法列表. */
    AlgorithmList m_AlgorithmList;

    /** @brief 内部算法列表. */
    InternalAlgorithmMap m_InternalAlgorithmMap;

    /** @brief 外部组件DLL句柄. */
    HINSTANCE m_ComponentDllHandle;

private:
    wstring m_ComponentDllFileName;
    /** @brief 外部组件配置文件名, 用于存放所有外部组件DLL文件名. */
    wstring m_ComponentCfgFileName;
    /** @brief 算法配置文件名. */
    wstring m_AlgorithmCfgFileName;

public:
    /** @brief 获得平台类实例. */
    static Platform &GetInstance();

private:
    /** @brief 平台私有默认构造函数. */
    Platform();
    /** @brief 用于存储平台类唯一实例的指针. */
    static Platform *s_Instance;
    /** @brief 用于记录平台类的唯一实例是否已被创建. */
    static bool s_Initialized;

    /** @brief 平台配置文件名. */
    static LPCWSTR s_CfgFileName;
    /** @brief 用于在平台配置文件中查找外部组件配置文件名的关键字. */
    static LPCWSTR s_ComponentDllFileNameKey;
    /** @brief 用于在平台配置文件中查找外部组件配置文件名的关键字. */
    static LPCWSTR s_ComponentCfgFileNameKey;
    /** @brief 用于在平台配置文件中查找算法配置文件名的关键字. */
    static LPCWSTR s_AlgorithmCfgFileNameKey;
};

#endif // __PLATFORM_H__
