#include "component.h"
#include "image_processing_ifaces.h"

#include "external_data.h"
#include "image.h"
#include "add.h"
#include "sub.h"
#include "output_external_data.h"
#include "output_image.h"

extern "C" __declspec(dllexport) void RegisterInterfaceType(InterfaceTypeMap &interfaceTypeMap)
{
    InterfaceType interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_EXTERNAL_DATA;
    interfaceType.InterfaceName = TEXT("数据");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_IMAGE;
    interfaceType.InterfaceName = TEXT("图像");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_IMAGE_ALGORITHM;
    interfaceType.InterfaceName = TEXT("图像算法");
    interfaceTypeMap[interfaceType.InterfaceId] = interfaceType;

    interfaceType.InterfaceId = CLIENT_CIID_OUTPUT_FILE;
    interfaceType.InterfaceName = TEXT("输出");
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
    componentType.InterfaceId = CLIENT_CIID_IMAGE_ALGORITHM;
    componentType.Factory = (ComponentFactory)Add::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = Sub::s_ComponentId;
    componentType.TypeName = Sub::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_IMAGE_ALGORITHM;
    componentType.Factory = (ComponentFactory)Sub::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = OutputExternalData::s_ComponentId;
    componentType.TypeName = OutputExternalData::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_OUTPUT_FILE;
    componentType.Factory = (ComponentFactory)OutputExternalData::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = OutputImage::s_ComponentId;
    componentType.TypeName = OutputImage::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_OUTPUT_FILE;
    componentType.Factory = (ComponentFactory)OutputImage::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;
}
