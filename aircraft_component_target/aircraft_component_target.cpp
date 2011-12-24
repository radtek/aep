#include "component.h"
#include "aircraft_component_ifaces.h"
#include "missile.h"

extern "C" __declspec(dllexport) void RegisterInterfaceType(InterfaceTypeMap &interfaceTypeMap)
{
    InterfaceType interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_TARGET;
    interfaceType.InterfaceName = TEXT("Ä¿±ê");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;
}

extern "C" __declspec(dllexport) void RegisterComponentType(ComponentTypeMap &componentTypeMap)
{
    ComponentType componentType;

    componentType.TypeId = Missile::s_ComponentId;
    componentType.TypeName = Missile::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_TARGET;
    componentType.Factory = (ComponentFactory)Missile::Factory;
    componentTypeMap[componentType.TypeId] = componentType;
}
