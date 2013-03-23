/**
* @file
* @brief 外部数据类cpp文件.
* @author ruoxi
*
* 实现了外部数据类.
*/

#include "stdafx.h"

#include "utility.h"
#include <fstream>
#include <iostream>

#include "algorithm_evaluate.h"

using namespace std;

AlgorithmEvaluate::AlgorithmEvaluate()
{
    m_Input = new IImageAlgorithmOutput(0);
}

AlgorithmEvaluate::~AlgorithmEvaluate()
{
    delete m_Input;
}

UINT32 AlgorithmEvaluate::GetInterfaceTypeId()
{
    return s_InterfaceId;
}

UINT32 AlgorithmEvaluate::GetTypeId()
{
    return s_ComponentId;
}

void AlgorithmEvaluate::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << CString(m_FilePath.c_str());
}

void AlgorithmEvaluate::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> str;
    m_FilePath = str;
}

void AlgorithmEvaluate::Destroy()
{
    delete this;
}

void *AlgorithmEvaluate::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 AlgorithmEvaluate::GetId()
{
    return m_Id;
}

void AlgorithmEvaluate::SetId(UINT32 id)
{
    m_Id = id;
}

wstring AlgorithmEvaluate::GetName()
{
    return m_Name;
}

void AlgorithmEvaluate::SetName(wstring name)
{
    m_Name = name;
}

void AlgorithmEvaluate::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_FILE_PATH;
    attribute.Name = TEXT("数据文件路径");
    attribute.Type = Attribute::TYPE_STRING;
    attributeList.push_back(attribute);
}

RC AlgorithmEvaluate::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_FILE_PATH:
        *((wstring *)attr) = m_FilePath;
        break;
    }

    return rc;
}

RC AlgorithmEvaluate::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_FILE_PATH:
        m_FilePath = *((wstring *)attr);
        break;
    }

    return rc;
}

bool AlgorithmEvaluate::Connect(IComponent *component)
{
    return false;
}

IComponent *AlgorithmEvaluate::Clone()
{
    AlgorithmEvaluate *ae = new AlgorithmEvaluate();
    ae->m_FilePath = m_FilePath;
    ae->m_Id = m_Id;
    ae->m_Name = m_Name;
    return ae;
}

void AlgorithmEvaluate::Reset()
{
    m_Input->Reset();
}

RC AlgorithmEvaluate::Config()
{
    RC rc;

    return rc;
}

RC AlgorithmEvaluate::SetInput(IData *input)
{
    if (NULL == input)
    {
        return RC::COMPONENT_SETINPUT_ERROR;
    }

    IImageAlgorithmOutput *imageAlgorithmOutput = (IImageAlgorithmOutput *)(input->GetInterface(CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT));
    if (NULL != imageAlgorithmOutput)
    {
        m_Input->m_ImageAlgorithm = imageAlgorithmOutput->m_ImageAlgorithm;
        return OK;
    }

    return RC::COMPONENT_SETINPUT_ERROR;
}

RC AlgorithmEvaluate::Run(bool input)
{
    RC rc;

    if (!Utility::FileExists(m_FilePath.c_str()))
    {
        if (!Utility::CreateFileNested(m_FilePath.c_str()))
        {
            return RC::FILE_OPEN_ERROR;
        }
    }
    wofstream ofs(m_FilePath.c_str());
    if (!ofs)
    {
        return RC::FILE_OPEN_ERROR;
    }
    const vector<UINT32> &cpuPercentage = m_Input->m_ImageAlgorithm->GetCpuPercentage();
    const vector<UINT32> &memoryUsageKB = m_Input->m_ImageAlgorithm->GetMemoryUsageKB();
    const vector<UINT64> &ns = m_Input->m_ImageAlgorithm->GetNS();
    ofs << cpuPercentage.size() << endl;
    for (UINT32 i = 0; i < cpuPercentage.size(); ++i)
    {
        ofs << cpuPercentage[i] << TEXT(' ') << memoryUsageKB[i] << TEXT(' ') << ns[i] << endl;
    }
    ofs.close();

    return rc;
}

RC AlgorithmEvaluate::GetOutput(IData *&output)
{
    return RC::COMPONENT_GETOUTPUT_ERROR;
}

AlgorithmEvaluate *AlgorithmEvaluate::Factory()
{
    AlgorithmEvaluate *ae = new AlgorithmEvaluate;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    ae->m_Name = name;
    ++s_Count;
    return ae;
}

LPCWSTR AlgorithmEvaluate::s_ComponentName = TEXT("算法评估");

UINT32 AlgorithmEvaluate::s_Count = 0;
