/**
* @file
* @brief 平台cpp文件.
* @author ruoxi
*
* 实现了平台类.
*/

#include "stdafx.h"

#include "platform.h"
#include "component.h"

Platform &Platform::GetInstance()
{
    if (!s_Initialized)
    {
        s_Instance = new Platform;
        s_Initialized = true;
    }
    return *s_Instance;
}

Platform::Platform()
{
}

Platform *Platform::s_Instance = NULL;

bool Platform::s_Initialized = false;

void GetComponentList(ComponentList &componentList)
{
    componentList = Platform::GetInstance().GetComponentList();
}

RC Platform::LoadComponentDll(LPCWSTR fileName)
{
    m_DllHandle = LoadLibrary(fileName);

    if (!m_DllHandle)
    {
        return RC::PLATFORM_LOADDLL_ERROR;
    }

    return OK;
}

RC Platform::RegisterComponent()
{
    RC rc;

    Component::RegisterComponentFunc func =
        (Component::RegisterComponentFunc)GetProcAddress(
        (HMODULE)m_DllHandle,
        Component::RegisterComponentFuncName);

    if (!func)
    {
        return RC::PLATFORM_REGISTERCLIENTCOMPONENT_ERROR;
    }

    func(m_ComponentInfoList, (Component::GetComponentListFunc)::GetComponentList);

    return rc;
}

RC Platform::UnloadComponentDll()
{
    FreeLibrary((HMODULE)m_DllHandle);
    return OK;
}

ComponentInfoList &Platform::GetComponentInfoList()
{
    return m_ComponentInfoList;
}

ComponentList &Platform::GetComponentList()
{
    return m_ComponentList;
}
