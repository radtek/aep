#include "component.h"
#include "image_processing_ifaces.h"

#include "external_data.h"
#include "image.h"
#include "dat_image.h"
#include "external_data_scissor.h"
#include "image_scissor.h"
#include "external_data_batch.h"
#include "image_batch.h"
#include "dat_image_batch.h"
#include "image_algorithm.h"
#include "add.h"
#include "sub.h"
#include "output_external_data.h"
#include "output_image.h"
#include "output_external_data_batch.h"
#include "output_image_batch.h"
#include "algorithm_evaluate.h"
#include "transfer_file.h"

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

    interfaceType.InterfaceId = CLIENT_CIID_TRANSFER;
    interfaceType.InterfaceName = TEXT("传输");
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

    componentType.TypeId = DatImage::s_ComponentId;
    componentType.TypeName = DatImage::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_IMAGE;
    componentType.Factory = (ComponentFactory)DatImage::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = ExternalDataScissor::s_ComponentId;
    componentType.TypeName = ExternalDataScissor::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_EXTERNAL_DATA;
    componentType.Factory = (ComponentFactory)ExternalDataScissor::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = ImageScissor::s_ComponentId;
    componentType.TypeName = ImageScissor::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_IMAGE;
    componentType.Factory = (ComponentFactory)ImageScissor::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = ExternalDataBatch::s_ComponentId;
    componentType.TypeName = ExternalDataBatch::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_EXTERNAL_DATA;
    componentType.Factory = (ComponentFactory)ExternalDataBatch::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = ImageBatch::s_ComponentId;
    componentType.TypeName = ImageBatch::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_IMAGE;
    componentType.Factory = (ComponentFactory)ImageBatch::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = DatImageBatch::s_ComponentId;
    componentType.TypeName = DatImageBatch::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_IMAGE;
    componentType.Factory = (ComponentFactory)DatImageBatch::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = ImageAlgorithm::s_ComponentId;
    componentType.TypeName = ImageAlgorithm::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_IMAGE_ALGORITHM;
    componentType.Factory = (ComponentFactory)ImageAlgorithm::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    /*
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
    */

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

    componentType.TypeId = OutputExternalDataBatch::s_ComponentId;
    componentType.TypeName = OutputExternalDataBatch::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_OUTPUT_FILE;
    componentType.Factory = (ComponentFactory)OutputExternalDataBatch::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = OutputImageBatch::s_ComponentId;
    componentType.TypeName = OutputImageBatch::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_OUTPUT_FILE;
    componentType.Factory = (ComponentFactory)OutputImageBatch::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = AlgorithmEvaluate::s_ComponentId;
    componentType.TypeName = AlgorithmEvaluate::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_OUTPUT_FILE;
    componentType.Factory = (ComponentFactory)AlgorithmEvaluate::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;

    componentType.TypeId = TransferFile::s_ComponentId;
    componentType.TypeName = TransferFile::s_ComponentName;
    componentType.InterfaceId = CLIENT_CIID_TRANSFER;
    componentType.Factory = (ComponentFactory)TransferFile::Factory;
    componentType.DllHandle = DllHandle;
    componentTypeMap[componentType.TypeId] = componentType;
}

PlatformService *g_PlatformService = NULL;

extern "C" __declspec(dllexport) void SetPlatformService(PlatformService *platformService)
{
    g_PlatformService = platformService;
}
