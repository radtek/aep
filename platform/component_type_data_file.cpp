#include "component_type_data_file.h"
#include "component.h"

ComponentTypeDataFile::ComponentTypeDataFile(wstring fileName)
:
DataFile(fileName)
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

    HINSTANCE componentDllHandle = LoadLibrary(dllFileName.c_str());

    if (!componentDllHandle)
    {
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
        registerComponentTypeFunc(m_ComponentTypeMap);
    }

    return rc;
}
