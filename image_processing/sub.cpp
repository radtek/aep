/**
* @file
* @brief 减法类cpp文件.
* @author ruoxi
*
* 实现了减法类.
*/

#include "sub.h"
#include "array_data.h"

Sub::Sub()
:
m_Input(NULL),
m_TestParam(0)
{
    ArrayData *arrayData = new ArrayData;
    m_Output = (IArrayData *)(arrayData->GetInterface(CLIENT_CIID_ARRAY_DATA));
}

Sub::~Sub()
{
    delete m_Output;
}

UINT32 Sub::GetTypeId()
{
    return s_ComponentId;
}

void Sub::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << m_TestParam;
}

void Sub::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> m_TestParam;
}

void Sub::Destroy()
{
    delete this;
}

void *Sub::GetInterface(UINT32 iid)
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

UINT32 Sub::GetId()
{
    return m_Id;
}

void Sub::SetId(UINT32 id)
{
    m_Id = id;
}

wstring Sub::GetName()
{
    return m_Name;
}

void Sub::SetName(wstring name)
{
    m_Name = name;
}

void Sub::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_TEST_PARAM;
    attribute.Name = TEXT("测试参数");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);
}

RC Sub::GetAttribute(UINT32 aid, void *attr)
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

RC Sub::SetAttribute(UINT32 aid, void *attr)
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

bool Sub::Connect(IComponent *component)
{
    return false;
}

bool Sub::SetInput(IData *input)
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

IData *Sub::GetOutput()
{
    if (NULL == m_Output)
    {
        return NULL;
    }

    return (IData *)(m_Output->GetInterface(CIID_IDATA));
}

IARC Sub::Run()
{
    IARC iarc;

    // FIXME

    return iarc;
}

Sub *Sub::Factory()
{
    Sub *sub = new Sub;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    sub->m_Name = name;
    ++s_Count;
    delete[] name;
    return sub;
}

LPCWSTR Sub::s_ComponentName = TEXT("减法");

UINT32 Sub::s_Count = 0;
