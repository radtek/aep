/**
* @file
* @brief 飞行器类cpp文件.
* @author ruoxi
*
* 实现了飞行器类.
*/

#include "alm.h"

ALM::ALM()
{
}

ALM::~ALM()
{
}

UINT32 ALM::GetTypeId()
{
    return s_ComponentId;
}

void ALM::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << m_Name.c_str();

    m_Velocity.Save(ar);
    m_Acceleration.Save(ar);
}

void ALM::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    m_Velocity.Load(ar);
    m_Acceleration.Load(ar);
}

void ALM::Destroy()
{
    delete this;
}

void *ALM::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_MOTION == iid)
    {
        iface = static_cast<IMotion *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 ALM::GetId()
{
    return m_Id;
}

void ALM::SetId(UINT32 id)
{
    m_Id = id;
}

wstring ALM::GetName()
{
    return m_Name;
}

void ALM::SetName(wstring name)
{
    m_Name = name;
}

void ALM::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = ALMAID_V_X;
    attribute.Name = TEXT("初始速度X");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);

    attribute.Id = ALMAID_V_Y;
    attribute.Name = TEXT("初始速度Y");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);

    attribute.Id = ALMAID_V_Z;
    attribute.Name = TEXT("初始速度Z");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);

    attribute.Id = ALMAID_A_X;
    attribute.Name = TEXT("初始加速度X");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);

    attribute.Id = ALMAID_A_Y;
    attribute.Name = TEXT("初始加速度Y");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);

    attribute.Id = ALMAID_A_Z;
    attribute.Name = TEXT("初始加速度Z");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);
}

RC ALM::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case ALMAID_V_X:
        *((double *)attr) = m_Velocity.x;
        break;
    case ALMAID_V_Y:
        *((double *)attr) = m_Velocity.y;
        break;
    case ALMAID_V_Z:
        *((double *)attr) = m_Velocity.z;
        break;
    case ALMAID_A_X:
        *((double *)attr) = m_Acceleration.x;
        break;
    case ALMAID_A_Y:
        *((double *)attr) = m_Acceleration.y;
        break;
    case ALMAID_A_Z:
        *((double *)attr) = m_Acceleration.z;
        break;
    }

    return rc;
}

RC ALM::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case ALMAID_V_X:
        m_Velocity.x = *((double *)attr);
        break;
    case ALMAID_V_Y:
        m_Velocity.y = *((double *)attr);
        break;
    case ALMAID_V_Z:
        m_Velocity.z = *((double *)attr);
        break;
    case ALMAID_A_X:
        m_Acceleration.x = *((double *)attr);
        break;
    case ALMAID_A_Y:
        m_Acceleration.y = *((double *)attr);
        break;
    case ALMAID_A_Z:
        m_Acceleration.z = *((double *)attr);
        break;
    }

    return rc;
}

bool ALM::Connect(IComponent *component)
{
    return false;
}

void ALM::Move(Vector &coordinate, double time)
{
    coordinate += (m_Velocity * time + m_Acceleration * time * time * 0.5);
    m_Velocity += (m_Acceleration * time);
}

ALM *ALM::Factory()
{
    ALM *alm = new ALM;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    alm->m_Name = name;
    ++s_Count;
    delete[] name;
    return alm;
}

LPCWSTR ALM::s_ComponentName = TEXT("匀加速直线运动");

UINT32 ALM::s_Count = 0;
