/**
* @file
* @brief 组件相关函数cpp文件.
* @author ruoxi
*
* 实现了组件相关函数.
*/

#include "component.h"
#include "utility.h"

LPCSTR Component::RegisterInterfaceTypeFuncName = "RegisterInterfaceType";

LPCSTR Component::RegisterComponentTypeFuncName = "RegisterComponentType";

LPCSTR Component::SetPlatformServiceFuncName = "SetPlatformService";

// LPCSTR Component::ValidateModelFuncName = "ValidateModel";

// LPCSTR Component::RunModelFuncName = "RunModel";

// Component::GetComponentListFunc Component::GetComponentList;

// LPCSTR Component::RegisterGetComponentListFuncFuncName = "RegisterGetComponentListFunc";

RC IAlgorithm::Run()
{
    RC rc;

    BeforeRun();
    rc = InternalRun();
    AfterRun();

    BeforeRun();

    return rc;
}

// UINT64 IAlgorithm::m_NS;
// UINT32 IAlgorithm::m_MemoryUsageKB;

UINT64 IAlgorithm::GetNS()
{
    return m_NS;
}

UINT32 IAlgorithm::GetMemoryUsageKB()
{
    return m_MemoryUsageKB;
}

UINT32 IAlgorithm::GetCpuPercentage()
{
    return Utility::GetCpuPercentage();
}

void IAlgorithm::BeforeRun()
{
    m_NS = Utility::GetNS();
    m_MemoryUsageKB = Utility::GetMemoryUsageKB();
}

void IAlgorithm::AfterRun()
{
    m_NS = Utility::GetNS() - m_NS;
    m_MemoryUsageKB = Utility::GetMemoryUsageKB() - m_MemoryUsageKB;
}
