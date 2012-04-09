/**
* @file
* @brief 导弹类cpp文件.
* @author ruoxi
*
* 实现了导弹类.
*/

#include "missile.h"

Missile::Missile()
:
m_Motion(NULL)
{
}

Missile::~Missile()
{
}

UINT32 Missile::GetTypeId()
{
    return s_ComponentId;
}

void Missile::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str());

    m_Coordinate.Save(ar);
}

void Missile::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    m_Coordinate.Load(ar);
}

void Missile::Destroy()
{
    delete this;
}

void *Missile::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_TARGET == iid)
    {
        iface = static_cast<ITarget *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 Missile::GetId()
{
    return m_Id;
}

void Missile::SetId(UINT32 id)
{
    m_Id = id;
}

wstring Missile::GetName()
{
    return m_Name;
}

void Missile::SetName(wstring name)
{
    m_Name = name;
}

void Missile::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = AAID_COORD_X;
    attribute.Name = TEXT("初始位置X");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);

    attribute.Id = AAID_COORD_Y;
    attribute.Name = TEXT("初始位置Y");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);

    attribute.Id = AAID_COORD_Z;
    attribute.Name = TEXT("初始位置Z");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);
}

RC Missile::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_COORD_X:
        *((double *)attr) = m_Coordinate.x;
        break;
    case AAID_COORD_Y:
        *((double *)attr) = m_Coordinate.y;
        break;
    case AAID_COORD_Z:
        *((double *)attr) = m_Coordinate.z;
        break;
    }

    return rc;
}

RC Missile::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case AAID_COORD_X:
        m_Coordinate.x = *((double *)attr);
        break;
    case AAID_COORD_Y:
        m_Coordinate.y = *((double *)attr);
        break;
    case AAID_COORD_Z:
        m_Coordinate.z = *((double *)attr);
        break;
    }

    return rc;
}

bool Missile::Connect(IComponent *component)
{
    IMotion *motion = (IMotion *)component->GetInterface(CLIENT_CIID_MOTION);
    if (NULL != motion)
    {
        m_Motion = motion;
        return true;
    }
    return false;
}

void Missile::Fly(double time)
{
    m_Motion->Move(m_Coordinate, time);
}

Vector Missile::GetCurrentCoordinate()
{
    return m_Coordinate;
}

Missile *Missile::Factory()
{
    Missile *missile = new Missile;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    missile->m_Name = name;
    ++s_Count;
    delete[] name;
    return missile;
}

LPCWSTR Missile::s_ComponentName = TEXT("导弹");

UINT32 Missile::s_Count = 0;
