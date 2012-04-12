/**
* @file
* @brief 加法类cpp文件.
* @author ruoxi
*
* 实现了加法类.
*/

#include "add.h"
#include "array_data.h"

Add::Add()
:
m_Input(NULL),
m_TestParam(0)
{
    ArrayData *arrayData = new ArrayData;
    m_Output = (IArrayData *)(arrayData->GetInterface(CLIENT_CIID_ARRAY_DATA));
}

Add::~Add()
{
    delete m_Output;
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

bool Add::SetInput(IData *input)
{
    if (NULL == input)
    {
        return false;
    }

    IArrayData *arrayData = (IArrayData *)(input->GetInterface(CLIENT_CIID_ARRAY_DATA));
    if (NULL == arrayData)
    {
        return false;
    }

    m_Input = arrayData;

    return true;
}

IData *Add::GetOutput()
{
    if (NULL == m_Output)
    {
        return NULL;
    }

    return (IData *)(m_Output->GetInterface(CIID_IDATA));
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
