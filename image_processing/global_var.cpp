/**
* @file
* @brief 图像窗口类cpp文件.
* @author ruoxi
*
* 实现了图像窗口类.
*/

#include "stdafx.h"

#include "global_var.h"
#include "utility.h"
#include "matlab_helper.h"

using namespace std;

GlobalVar::GlobalVar()
:
m_Count(10),
m_Width(512),
m_Height(512),
m_Array(NULL)
{
}

GlobalVar::~GlobalVar()
{
    if (m_Array)
    {
        MatLabHelper::DestroyArray(m_Array);
        m_Array = 0;
    }
}

UINT32 GlobalVar::GetInterfaceTypeId()
{
    return s_InterfaceId;
}

UINT32 GlobalVar::GetTypeId()
{
    return s_ComponentId;
}

void GlobalVar::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << m_Count
        << m_Width
        << m_Height;
}

void GlobalVar::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> m_Count >> m_Width >> m_Height;
}

void GlobalVar::Destroy()
{
    delete this;
}

void *GlobalVar::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CIID_IGLOBAL_VAR == iid)
    {
        iface = static_cast<IGlobalVar *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 GlobalVar::GetId()
{
    return m_Id;
}

void GlobalVar::SetId(UINT32 id)
{
    m_Id = id;
}

wstring GlobalVar::GetName()
{
    return m_Name;
}

void GlobalVar::SetName(wstring name)
{
    m_Name = name;
}

void GlobalVar::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_COUNT;
    attribute.Name = TEXT("变量个数");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);

    attribute.Id = AAID_WIDTH;
    attribute.Name = TEXT("宽度");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);

    attribute.Id = AAID_HEIGHT;
    attribute.Name = TEXT("高度");
    attribute.Type = Attribute::TYPE_INT;
    attributeList.push_back(attribute);
}

RC GlobalVar::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_COUNT:
        *((UINT32 *)attr) = m_Count;
        break;
    case AAID_WIDTH:
        *((UINT32 *)attr) = m_Width;
        break;
    case AAID_HEIGHT:
        *((UINT32 *)attr) = m_Height;
        break;
    }

    return rc;
}

RC GlobalVar::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_COUNT:
        m_Count = *((UINT32 *)attr);
        break;
    case AAID_WIDTH:
        m_Width = *((UINT32 *)attr);
        break;
    case AAID_HEIGHT:
        m_Height = *((UINT32 *)attr);
        break;
    }

    return rc;
}

bool GlobalVar::Connect(IComponent *component)
{
    return false;
}

RC GlobalVar::Config()
{
    RC rc;

    return rc;
}

IComponent *GlobalVar::Clone()
{
    GlobalVar *var = new GlobalVar();
    var->m_Count = m_Count;
    var->m_Width = m_Width;
    var->m_Height = m_Height;
    return var;
}

void GlobalVar::Reset()
{
    if (m_Array)
    {
        MatLabHelper::DestroyArray(m_Array);
        m_Array = 0;
    }
}

RC GlobalVar::SetInput(IData *input)
{
    return RC::COMPONENT_SETINPUT_ERROR;
}

RC GlobalVar::Run(bool input)
{
    RC rc;

    // m_Array = mxCreateDoubleMatrix(m_Width, m_Height, mxREAL);
#if 1
    mwSize dim[1] = {m_Count};
    m_Array = mxCreateCellArray(1, dim);

    for (UINT32 i = 0; i < m_Count; ++i)
    {
        Array *cellArray = mxCreateDoubleMatrix(m_Width, m_Height, mxREAL);
        mxSetCell(m_Array, i, cellArray);
    }
#endif

    return rc;
}

RC GlobalVar::GetOutput(IData *&output)
{
    return OK;
}

Array *GlobalVar::GetData()
{
    return m_Array;
}

void GlobalVar::SetData(Array *data)
{
    if (m_Array)
    {
        MatLabHelper::DestroyArray(m_Array);
    }
    m_Array = data;
}

GlobalVar *GlobalVar::Factory()
{
    GlobalVar *var = new GlobalVar;
    CString name = s_ComponentName;
    name.AppendFormat(TEXT("%u"), s_Count + 1);
    var->m_Name = name;
    ++s_Count;
    return var;
}

LPCWSTR GlobalVar::s_ComponentName = TEXT("全局变量");

UINT32 GlobalVar::s_Count = 0;
