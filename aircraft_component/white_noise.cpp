#include "white_noise.h"

WhiteNoise *WhiteNoise::Factory()
{
    WhiteNoise *whiteNoise = new WhiteNoise;
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s%u"), s_ComponentName, s_Count);
    whiteNoise->m_Name = name;
    ++s_Count;
    delete[] name;
    return whiteNoise;
}

WhiteNoise::WhiteNoise()
:
m_Factor(0)
{
}

WhiteNoise::~WhiteNoise()
{
}

UINT32 WhiteNoise::GetTypeId()
{
    return s_ComponentId;
}

void WhiteNoise::Save(CArchive &ar)
{
    ar << s_ComponentId
        << m_Id
        << CString(m_Name.c_str())
        << m_Factor;
}

void WhiteNoise::Load(CArchive &ar)
{
    ar >> m_Id;

    CString str;
    ar >> str;
    m_Name = str;

    ar >> m_Factor;
}

void WhiteNoise::Destroy()
{
    delete this;
}

void *WhiteNoise::GetInterface(UINT32 iid)
{
    void *iface;

    if (CIID_ICOMPONENT == iid)
    {
        iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_NOISE == iid)
    {
        iface = static_cast<INoise *>(this);
    }
    else
    {
        iface = NULL;
    }
    return iface;
}

UINT32 WhiteNoise::GetId()
{
    return m_Id;
}

void WhiteNoise::SetId(UINT32 id)
{
    m_Id = id;
}

wstring WhiteNoise::GetName()
{
    return m_Name;
}

void WhiteNoise::SetName(wstring name)
{
    m_Name = name;
}

void WhiteNoise::GetAttributeList(AttributeList &attributeList)
{
    Attribute attribute;

    attribute.Id = WNAID_COORD_FACTOR;
    attribute.Name = TEXT("°×ÔëÉùÓ°ÏìÒò×Ó");
    attribute.Type = Attribute::TYPE_DOUBLE;
    attributeList.push_back(attribute);
}

RC WhiteNoise::GetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case WNAID_COORD_FACTOR:
        *((double *)attr) = m_Factor;
        break;
    }

    return rc;
}

RC WhiteNoise::SetAttribute(UINT32 aid, void *attr)
{
    RC rc;

    switch (aid)
    {
    case WNAID_COORD_FACTOR:
        m_Factor = *((double *)attr);
        break;
    }

    return rc;
}

bool WhiteNoise::Connect(IComponent *component)
{
    return false;
}

double WhiteNoise::Affect(double data)
{
    double value = ((double)(rand()) / (double)(RAND_MAX) - 0.5) * m_Factor * data;
    return data + value;
}

double WhiteNoise::GetMean()
{
    return m_Factor / 2;
}

double WhiteNoise::GetVariance()
{
    return m_Factor * m_Factor / 2;
}

LPCWSTR WhiteNoise::s_ComponentName = TEXT("°×ÔëÉù");

UINT32 WhiteNoise::s_Count = 0;