#include "aircraft_measure.h"
#include "uniform_linear_motion.h"
#include "acceleration_linear_motion.h"
#include "aircraft.h"
#include "resource.h"

void RegisterClientComponent(ComponentInfoList &componentInfoList)
{
    ComponentInfo componentInfo;

    componentInfo.typeName = AccelerationLinearMotionTypeName;
    componentInfo.attributeList = AccelerationLinearMotionAttributeList;
    componentInfo.factory = (ComponentFactory)AccelerationLinearMotionFactory;
    componentInfo.iconId = IDI_MOTION;
    componentInfoList.push_back(componentInfo);

    componentInfo.typeName = UniformLinearMotionTypeName;
    componentInfo.attributeList = UniformLinearMotionAttributeList;
    componentInfo.factory = (ComponentFactory)UniformLinearMotionFactory;
    componentInfo.iconId = IDI_MOTION;
    componentInfoList.push_back(componentInfo);

    componentInfo.typeName = AircraftTypeName;
    componentInfo.attributeList = AircraftAttributeList;
    componentInfo.factory = (ComponentFactory)AircraftFactory;
    componentInfo.iconId = IDI_AIRCRAFT;
    componentInfoList.push_back(componentInfo);
}
