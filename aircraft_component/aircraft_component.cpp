#include "component.h"
#include "aircraft_component_ifaces.h"
#include "aircraft.h"
#include "ulm.h"
#include "alm.h"

extern "C" __declspec(dllexport) void RegisterInterfaceInfo(InterfaceInfoList &interfaceInfoList)
{
    InterfaceInfo interfaceInfo;

    interfaceInfo.interfaceId = CLIENT_CIID_AIRCRAFT;
    interfaceInfo.interfaceName = TEXT("·ÉÐÐÆ÷");
    interfaceInfoList.push_back(interfaceInfo);

    interfaceInfo.interfaceId = CLIENT_CIID_MOTION;
    interfaceInfo.interfaceName = TEXT("ÔË¶¯");
    interfaceInfoList.push_back(interfaceInfo);
}

extern "C" __declspec(dllexport) void RegisterComponentInfo(ComponentInfoList &componentInfoList)
{
    ComponentInfo componentInfo;

    componentInfo.componentId = Aircraft::s_ComponentId;
    componentInfo.componentName = Aircraft::s_ComponentName;
    componentInfo.interfaceId = CLIENT_CIID_AIRCRAFT;
    componentInfo.factory = (ComponentFactory)Aircraft::Factory;
    componentInfoList.push_back(componentInfo);

    componentInfo.componentId = ULM::s_ComponentId;
    componentInfo.componentName = ULM::s_ComponentName;
    componentInfo.interfaceId = CLIENT_CIID_MOTION;
    componentInfo.factory = (ComponentFactory)ULM::Factory;
    componentInfoList.push_back(componentInfo);

    componentInfo.componentId = ALM::s_ComponentId;
    componentInfo.componentName = ALM::s_ComponentName;
    componentInfo.interfaceId = CLIENT_CIID_MOTION;
    componentInfo.factory = (ComponentFactory)ALM::Factory;
    componentInfoList.push_back(componentInfo);
}

extern "C" __declspec(dllexport) void RegisterGetComponentListFunc(Component::GetComponentListFunc getComponentListFunc)
{
    Component::GetComponentList = getComponentListFunc;
}
