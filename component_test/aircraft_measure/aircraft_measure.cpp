#include "aircraft_measure.h"

ComponentInfo *RegisterAllComponents()
{
    ComponentInfo *componentInfoList = new ComponentInfo[3];

    componentInfoList[0].typeName = AccelerationLinearMotionTypeName;
    componentInfoList[0].attributeList = AccelerationLinearMotionAttributeList;
    componentInfoList[0].factory = (ComponentFactory)AccelerationLinearMotionFactory;

    componentInfoList[1].typeName = UniformLinearMotionTypeName;
    componentInfoList[1].attributeList = UniformLinearMotionAttributeList;
    componentInfoList[1].factory = (ComponentFactory)UniformLinearMotionFactory;

    componentInfoList[2].typeName = AircraftTypeName;
    componentInfoList[2].attributeList = AircraftAttributeList;
    componentInfoList[2].factory = (ComponentFactory)AircraftFactory;

    return componentInfoList;
}