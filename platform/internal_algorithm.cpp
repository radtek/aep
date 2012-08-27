/**
* @file
* @brief 内部算法组件cpp文件.
* @author ruoxi
*
* 实现了内部算法类.
*/

#include "internal_algorithm.h"

#include "algorithm_helper.h"

#include <algorithm>

using namespace std;

/**
* 构造一个空的内部算法实例.
*/
InternalAlgorithm::InternalAlgorithm()
{
}

/**
* @param id 算法ID
* @param name 算法名称.
* @param dllFileName 算法DLL文件名.
* @param funcName 算法入口函数名称.
*
* 通过参数配置一个内部算法实例.
*/
InternalAlgorithm::InternalAlgorithm(UINT32 id,
                                     wstring name,
                                     wstring dllFileName,
                                     wstring funcName)
                                     :
m_Id(id),
m_Name(name),
m_DllFileName(dllFileName),
m_FuncName(funcName)
{
}

InternalAlgorithm::~InternalAlgorithm()
{
}

UINT32 InternalAlgorithm::GetTypeId()
{
    return s_ComponentId;
}

void InternalAlgorithm::Save(CArchive &ar)
{
    ar << m_Id;
}

void InternalAlgorithm::Load(CArchive &ar)
{
}

void InternalAlgorithm::Destroy()
{
    // delete this;
}

void *InternalAlgorithm::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CIID_IALGORITHM == iid)
    {
        iface = static_cast<IAlgorithm *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 InternalAlgorithm::GetId()
{
    return m_Id;
}

void InternalAlgorithm::SetId(UINT32 id)
{
    m_Id = id;
}

wstring InternalAlgorithm::GetName()
{
    return m_Name;
}

void InternalAlgorithm::SetName(wstring name)
{
    m_Name = name;
}

void InternalAlgorithm::GetAttributeList(AttributeList &attributeList)
{
}

RC InternalAlgorithm::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    return rc;
}

RC InternalAlgorithm::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    return rc;
}

bool InternalAlgorithm::Connect(IComponent *component)
{
    IParam *param = (IParam *)component->GetInterface(CIID_IPARAM);
    if (NULL != param)
    {
        if (find(m_ParamList.begin(), m_ParamList.end(), param) == m_ParamList.end())
        {
            m_ParamList.push_back(param);
        }
        return true;
    }
    return false;
}

IComponent *InternalAlgorithm::Clone()
{
    return NULL;
}

void InternalAlgorithm::Reset()
{
}

RC InternalAlgorithm::Config()
{
    RC rc;

    return rc;
}

RC InternalAlgorithm::SetInput(IData *input)
{
    RC rc;

    // FIXME

    return rc;
}

RC InternalAlgorithm::GetOutput(IData *&output)
{
    RC rc;

    // FIXME

    return rc;
}

RC InternalAlgorithm::Run()
{
    RC rc;

    CHECK_RC(AlgorithmHelper::RunFunc(m_DllFileName, m_FuncName, m_ParamList));

    return rc;
}

bool InternalAlgorithm::IsEntrance()
{
    return false;
}

LPCWSTR InternalAlgorithm::s_ComponentName = TEXT("内部算法");
