#include "component_type_data_file.h"
#include "component.h"
#include "utility.h"

ComponentTypeDataFile::ComponentTypeDataFile(wstring fileName, PlatformService *platformService)
: DataFile(fileName)
, m_PlatformService(platformService)
{
}

ComponentTypeDataFile::~ComponentTypeDataFile()
{
}

InterfaceTypeMap &ComponentTypeDataFile::GetInterfaceTypeMap()
{
    return m_InterfaceTypeMap;
}

ComponentTypeMap &ComponentTypeDataFile::GetComponentTypeMap()
{
    return m_ComponentTypeMap;
}

RC ComponentTypeDataFile::ParseLine(const wstring &line)
{
    RC rc;

    wistringstream ist(line);

    wstring dllFileName;
    ist >> dllFileName;

    // FIXME: When release?
    HINSTANCE componentDllHandle = LoadLibrary(dllFileName.c_str());

    if (!componentDllHandle)
    {
        Utility::PromptLastErrorMessage();
        return RC::PLATFORM_LOADDLL_ERROR;
    }

    Component::RegisterInterfaceTypeFunc registerInterfaceTypeFunc =
        (Component::RegisterInterfaceTypeFunc)GetProcAddress(
        (HMODULE)componentDllHandle,
        Component::RegisterInterfaceTypeFuncName);

    if (registerInterfaceTypeFunc)
    {
        registerInterfaceTypeFunc(m_InterfaceTypeMap);
    }

    Component::RegisterComponentTypeFunc registerComponentTypeFunc =
        (Component::RegisterComponentTypeFunc)GetProcAddress(
        (HMODULE)componentDllHandle,
        Component::RegisterComponentTypeFuncName);

    if (registerComponentTypeFunc)
    {
        registerComponentTypeFunc(m_ComponentTypeMap, componentDllHandle);
    }

    Component::SetPlatformServiceFunc setPlatformServiceFunc =
        (Component::SetPlatformServiceFunc)GetProcAddress(
        (HMODULE)componentDllHandle,
        Component::SetPlatformServiceFuncName);

    if (setPlatformServiceFunc)
    {
        setPlatformServiceFunc(m_PlatformService);
    }

    return rc;
}
