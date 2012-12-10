#ifndef __COMPONENT_TYPE_DATA_FILE_H__
#define __COMPONENT_TYPE_DATA_FILE_H__

#include "data_file.h"
#include "interfaces.h"

class ComponentTypeDataFile : public DataFile
{
public:
    ComponentTypeDataFile(wstring fileName, PlatformService *platformService);
    virtual ~ComponentTypeDataFile();

    InterfaceTypeMap &GetInterfaceTypeMap();
    ComponentTypeMap &GetComponentTypeMap();
protected:
    virtual RC ParseLine(const wstring &line);

protected:
    InterfaceTypeMap m_InterfaceTypeMap;
    ComponentTypeMap m_ComponentTypeMap;
    PlatformService *m_PlatformService;
};

#endif // __COMPONENT_TYPE_DATA_FILE_H__
