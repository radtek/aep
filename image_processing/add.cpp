/**
* @file
* @brief 加法类cpp文件.
* @author ruoxi
*
* 实现了加法类.
*/

#include "add.h"

Add::Add()
:
m_TestParam(0)
{
    m_Input1 = new IImageAlgorithmInput1;
    m_Input2 = new IImageAlgorithmInput2;
    m_Output1 = new IImageAlgorithmOutput1;
    m_Output2 = new IImageAlgorithmOutput2;
}

Add::~Add()
{
    delete m_Output1;
    delete m_Output2;
}

UINT32 Add::GetTypeId()
{
    return s_ComponentId;
}

void Add::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << m_TestParam;
}

void Add::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> m_TestParam;
}

void Add::Destroy()
{
    delete this;
}

void *Add::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_IMAGE == iid)
    {
        iface = static_cast<IImageAlgorithm *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 Add::GetId()
{
    return m_Id;
}

void Add::SetId(UINT32 id)
{
    m_Id = id;
}

wstring Add::GetName()
{
    return m_Name;
}

void Add::SetName(wstring name)
{
    m_Name = name;
}

void Add::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_TEST_PARAM;
    attribute.Name = TEXT("测试参数");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);
}

RC Add::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_TEST_PARAM:
        *((double *)attr) = m_TestParam;
        break;
    }

    return rc;
}

RC Add::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_TEST_PARAM:
        m_TestParam = *((double *)attr);
        break;
    }

    return rc;
}

bool Add::Connect(IComponent *component)
{
    return false;
}

RC Add::SetInput(IData *data)
{
    if (NULL == data)
    {
        return RC::COMPONENT_SETINPUT_ERROR;
    }

    IExternalDataOutput *externalDataOutput = (IExternalDataOutput *)(data->GetInterface(CLIENT_CIID_EXTERNAL_DATA_OUTPUT));
    if (NULL != externalDataOutput)
    {
        m_Input1->m_Array = externalDataOutput->m_Array;
        return OK;
    }

    IImageOutput *imageOutput = (IImageOutput *)(data->GetInterface(CLIENT_CIID_IMAGE_OUTPUT));
    if (NULL != imageOutput)
    {
        m_Input2->m_Array = imageOutput->m_Array;
        return OK;
    }

    IImageAlgorithmOutput1 *imageAlgorithmOutput1 = (IImageAlgorithmOutput1 *)(data->GetInterface(CLIENT_CIID_IMAGE_ALGORITHM_OUTPUT1));
    if (NULL != imageAlgorithmOutput1)
    {
        m_Input2->m_Array = imageAlgorithmOutput1->m_Array;
        return OK;
    }

    return RC::COMPONENT_SETINPUT_ERROR;
}

RC Add::GetOutput1(IData *&output)
{
    if (NULL == m_Output1)
    {
        output = NULL;
        return RC::COMPONENT_GETOUTPUT_ERROR;
    }

    output = (IData *)(m_Output1->GetInterface(CIID_IDATA));
    if (NULL == output)
    {
        return RC::COMPONENT_GETOUTPUT_ERROR;
    }

    return OK;
}

RC Add::GetOutput2(IData *&output)
{
    if (NULL == m_Output2)
    {
        output = NULL;
        return RC::COMPONENT_GETOUTPUT_ERROR;
    }

    output = (IData *)(m_Output2->GetInterface(CIID_IDATA));
    if (NULL == output)
    {
        return RC::COMPONENT_GETOUTPUT_ERROR;
    }

    return OK;
}

IARC Add::Run()
{
    IARC iarc;

    // FIXME

    return iarc;
}

Add *Add::Factory()
{
    Add *add = new Add;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    add->m_Name = name;
    ++s_Count;
    delete[] name;
    return add;
}

LPCWSTR Add::s_ComponentName = TEXT("加法");

UINT32 Add::s_Count = 0;
