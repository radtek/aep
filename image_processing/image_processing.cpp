#include "component.h"
#include "image_processing_ifaces.h"

extern "C" __declspec(dllexport) void RegisterInterfaceType(InterfaceTypeMap &interfaceTypeMap)
{
    InterfaceType interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_DATA;
    interfaceType.InterfaceName = TEXT("����");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_IMAGE_ALGORITHM;
    interfaceType.InterfaceName = TEXT("ͼ���㷨");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;
}

extern "C" __declspec(dllexport) void RegisterComponentType(ComponentTypeMap &componentTypeMap)
{
    ComponentType componentType;

    /*
    componentType.TypeId = Missile::s_ComponentId;
    componentType.TypeName = Missile::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_TARGET;
    componentType.Factory = (ComponentFactory)Missile::Factory;
    componentTypeMap[componentType.TypeId] = componentType;
    */
}
