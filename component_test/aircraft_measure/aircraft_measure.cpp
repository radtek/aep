#include "aircraft_measure.h"
#include "uniform_linear_motion.h"
#include "acceleration_linear_motion.h"
#include "aircraft.h"

void RegisterClientComponent(ComponentInfoList &componentInfoList)
{
    ComponentInfo componentInfo;

    componentInfo.typeName = AccelerationLinearMotionTypeName;
    componentInfo.attributeList = AccelerationLinearMotionAttributeList;
    componentInfo.factory = (ComponentFactory)AccelerationLinearMotionFactory;
    componentInfoList.push_back(componentInfo);

    componentInfo.typeName = UniformLinearMotionTypeName;
    componentInfo.attributeList = UniformLinearMotionAttributeList;
    componentInfo.factory = (ComponentFactory)UniformLinearMotionFactory;
    componentInfoList.push_back(componentInfo);

    componentInfo.typeName = AircraftTypeName;
    componentInfo.attributeList = AircraftAttributeList;
    componentInfo.factory = (ComponentFactory)AircraftFactory;
    componentInfoList.push_back(componentInfo);
}
