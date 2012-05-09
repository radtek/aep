#include "component.h"
#include "image_processing_ifaces.h"

#include "external_data.h"
#include "image.h"
#include "add.h"
#include "sub.h"

extern "C" __declspec(dllexport) void RegisterInterfaceType(InterfaceTypeMap &interfaceTypeMap)
{
    InterfaceType interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_EXTERNAL_DATA;
    interfaceType.InterfaceName = TEXT("Êý¾Ý");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_IMAGE;
    interfaceType.InterfaceName = TEXT("Í¼Ïñ");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;

    interfaceType.InterfaceId = CIID_IALGORITHM;
    interfaceType.InterfaceName = TEXT("Í¼ÏñËã·¨");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;
}

extern "C" __declspec(dllexport) void RegisterComponentType(ComponentTypeMap &componentTypeMap, HINSTANCE DllHandle)
{
    ComponentType componentType;

    componentType.TypeId = ExternalData::s_ComponentId;
    componentType.TypeName = ExternalData::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_EXTERNAL_DATA;
    componentType.Factory = (ComponentFactory)ExternalData::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = Image::s_ComponentId;
    componentType.TypeName = Image::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_IMAGE;
    componentType.Factory = (ComponentFactory)Image::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = Add::s_ComponentId;
    componentType.TypeName = Add::s_ComponentName;
    componentType.InterfaceId = CIID_IALGORITHM;
    componentType.Factory = (ComponentFactory)Add::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = Sub::s_ComponentId;
    componentType.TypeName = Sub::s_ComponentName;
    componentType.InterfaceId = CIID_IALGORITHM;
    componentType.Factory = (ComponentFactory)Sub::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;
}
