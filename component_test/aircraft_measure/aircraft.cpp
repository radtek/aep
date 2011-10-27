/**
* @file
* @brief 飞行器类cpp文件.
* @author ruoxi
*
* 实现了飞行器类.
*/

#include "aircraft.h"
#include "aircraft_config_dlg.h"

Aircraft::Aircraft()
{
}

Aircraft::~Aircraft()
{
    delete[] m_Name;
}

RC Aircraft::GetInterface(UINT32 iid, void **iface)
{
    if (CIID_ICOMPONENT == iid)
    {
        *iface = static_cast<IComponent *>(this);
    }
    else if (CLIENT_CIID_AIRCRAFT == iid)
    {
        *iface = static_cast<IAircraft *>(this);
    }
    else
    {
        *iface = 0;
        return RC::COMPONENT_GETINTERFACE_ERROR;
    }
    return OK;
}

RC Aircraft::Config(ComponentList *list)
{
    // AFX_MANAGE_STATE(AfxGetStaticModuleState());
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CAircraftConfigDlg dlg(list);
    dlg.DoModal();
    delete[] m_Name;
    m_Name = new wchar_t[dlg.m_Name.GetLength() + 1];
    wsprintf(m_Name, TEXT("%s"), (LPWSTR)(LPCTSTR)dlg.m_Name);
    m_Name[dlg.m_Name.GetLength()] = 0;
    return OK;
}

RC Aircraft::Destroy()
{
    delete this;
    return OK;
}

RC Aircraft::GetName(LPWSTR *name)
{
    *name = m_Name;
    return OK;
}

RC Aircraft::GetAttribute(UINT32 aid, void **attr)
{
    if (ATTR_NAME == aid)
    {
        *attr = m_Name;
    }
    else if (ATTR_START_COORDINATE == aid)
    {
        *attr = m_StartCoordinate;
    }
    else if (ATTR_START_VELOCITY == aid)
    {
        *attr = m_StartVelocity;
    }
    else if (ATTR_CURRENT_COORDINATE == aid)
    {
        *attr = m_CurrentCoordinate;
    }
    else if (ATTR_CURRENT_VELOCITY == aid)
    {
        *attr = m_CurrentVelocity;
    }
    else if (ATTR_MOTION == aid)
    {
        *attr = m_Motion;
    }
    else
    {
        *attr = 0;
        return RC::COMPONENT_GETATTRIBUTE_ERROR;
    }
    return OK;
}

RC Aircraft::SetAttribute(UINT32 aid, void *attr)
{
    if (ATTR_NAME == aid)
    {
        m_Name = (LPWSTR)attr;
    }
    else if (ATTR_START_COORDINATE == aid)
    {
        m_StartCoordinate = static_cast<Vector *>(attr);
    }
    else if (ATTR_START_VELOCITY == aid)
    {
        m_StartVelocity = static_cast<Vector *>(attr);
    }
    else if (ATTR_CURRENT_COORDINATE == aid)
    {
        m_CurrentCoordinate = static_cast<Vector *>(attr);
    }
    else if (ATTR_CURRENT_VELOCITY == aid)
    {
        m_CurrentVelocity = static_cast<Vector *>(attr);
    }
    else if (ATTR_MOTION == aid)
    {
        m_Motion = static_cast<IMotion *>(attr);
    }
    else
    {
        return RC::COMPONENT_SETATTRIBUTE_ERROR;
    }
    return OK;
}

RC Aircraft::Fly(double second)
{
    RC rc;
    CHECK_RC(m_Motion->GetCurrentVelocity(*m_CurrentVelocity));
    CHECK_RC(m_Motion->Move(*m_CurrentCoordinate, second));
    return rc;
}

LPCWSTR AircraftTypeName = TEXT("Aircraft");

UINT32 AircraftAttributeList[] =
{
    #undef DEFINE_ATTR
    /** @brief 重定义飞行器属性的外包宏DEFINE_ATTR. */
    #define DEFINE_ATTR(a, msg) Aircraft::a,
    /** @brief 用来开启允许包含aircraft_attrs.h头文件的开关. */
    #define __USE_AIRCRAFT_ATTRS__
    #include "aircraft_attrs.h"
};

UINT32 AircraftCount = 0;

Aircraft *AircraftFactory()
{
    Aircraft *aircraft = new Aircraft();
    LPWSTR name = new wchar_t[256];
    wsprintf(name, TEXT("%s %u"), AircraftTypeName, AircraftCount);
    aircraft->m_Name = name;
    ++AircraftCount;
    return aircraft;
}

void AircraftDestroy(Aircraft *aircraft)
{
    delete aircraft;
}
