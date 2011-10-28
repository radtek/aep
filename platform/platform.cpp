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

    typedef void (*RegisterComponentFunc)(ComponentInfoList &componentInfoList);
    RegisterComponentFunc func =
        (RegisterComponentFunc)GetProcAddress(
        (HMODULE)m_DllHandle,
        Component::registerComponentFuncName);

    if (!func)
    {
        return RC::PLATFORM_REGISTERCLIENTCOMPONENT_ERROR;
    }

    func(m_ComponentInfoList);

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
