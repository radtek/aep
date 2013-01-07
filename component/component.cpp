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

RC IAlgorithm::Run(bool input)
{
    RC rc;

    BeforeRun();
    rc = InternalRun();
    AfterRun();

    return rc;
}

// UINT64 IAlgorithm::m_NS;
// UINT32 IAlgorithm::m_MemoryUsageKB;

const vector<UINT64>& IAlgorithm::GetNS()
{
    return m_NS;
}

const vector<UINT32>& IAlgorithm::GetMemoryUsageKB()
{
    return m_MemoryUsageKB;
}

const vector<UINT32>& IAlgorithm::GetCpuPercentage()
{
    return m_CpuPercentage;
}

void IAlgorithm::BeforeRun()
{
    m_BeforeMemoryUsageKB = Utility::GetMemoryUsageKB();
    m_BeforeCpuPercentage = Utility::GetCpuPercentage();
    m_BeforeNS = Utility::GetNS();
}

void IAlgorithm::AfterRun()
{
    m_AfterNS = Utility::GetNS();
    m_AfterCpuPercentage = Utility::GetCpuPercentage();
    m_AfterMemoryUsageKB = Utility::GetMaxMemoryUsageKB();

    m_NS.push_back(m_AfterNS - m_BeforeNS);
    m_MemoryUsageKB.push_back(m_AfterMemoryUsageKB - m_BeforeMemoryUsageKB);
    m_CpuPercentage.push_back(m_AfterCpuPercentage);
}
