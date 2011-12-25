#include "component.h"
#include "aircraft_component_ifaces.h"
#include "aircraft.h"
#include "ulm.h"
#include "alm.h"
#include "white_noise.h"
#include "atd.h"

extern "C" __declspec(dllexport) void RegisterInterfaceType(InterfaceTypeMap &interfaceTypeMap)
{
    InterfaceType interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_AIRCRAFT;
    interfaceType.InterfaceName = TEXT("飞行器");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_MOTION;
    interfaceType.InterfaceName = TEXT("运动");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_NOISE;
    interfaceType.InterfaceName = TEXT("噪声");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_REAL_VALUE;
    interfaceType.InterfaceName = TEXT("真实值");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;
}

extern "C" __declspec(dllexport) void RegisterComponentType(ComponentTypeMap &componentTypeMap)
{
    ComponentType componentType;

    componentType.TypeId = Aircraft::s_ComponentId;
    componentType.TypeName = Aircraft::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_AIRCRAFT;
    componentType.Factory = (ComponentFactory)Aircraft::Factory;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = ULM::s_ComponentId;
    componentType.TypeName = ULM::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_MOTION;
    componentType.Factory = (ComponentFactory)ULM::Factory;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = ALM::s_ComponentId;
    componentType.TypeName = ALM::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_MOTION;
    componentType.Factory = (ComponentFactory)ALM::Factory;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = WhiteNoise::s_ComponentId;
    componentType.TypeName = WhiteNoise::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_NOISE;
    componentType.Factory = (ComponentFactory)WhiteNoise::Factory;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = ATD::s_ComponentId;
    componentType.TypeName = ATD::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_REAL_VALUE;
    componentType.Factory = (ComponentFactory)ATD::Factory;
    componentTypeMap[componentType.TypeId] = componentType;
}

extern "C" __declspec(dllexport) void RegisterGetComponentListFunc(Component::GetComponentListFunc getComponentListFunc)
{
    Component::GetComponentList = getComponentListFunc;
}
