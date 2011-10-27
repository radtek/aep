#include "aircraft_measure.h"
#include "uniform_linear_motion.h"
#include "acceleration_linear_motion.h"
#include "aircraft.h"
#include "resource.h"

#include "stdafx.h"

void RegisterClientComponent(ComponentInfoList &componentInfoList)
{
    ComponentInfo componentInfo;
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    componentInfo.typeName = AccelerationLinearMotionTypeName;
    componentInfo.attributeList = AccelerationLinearMotionAttributeList;
    componentInfo.factory = (ComponentFactory)AccelerationLinearMotionFactory;
    componentInfo.destroy = (ComponentDestroy)AccelerationLinearMotionDestroy;
    componentInfo.iconHandle = AfxGetApp()->LoadIcon(IDI_MOTION_ICON); //IDI_MOTION_ICON;
    componentInfoList.push_back(componentInfo);

    componentInfo.typeName = UniformLinearMotionTypeName;
    componentInfo.attributeList = UniformLinearMotionAttributeList;
    componentInfo.factory = (ComponentFactory)UniformLinearMotionFactory;
    componentInfo.destroy = (ComponentDestroy)UniformLinearMotionDestroy;
    componentInfo.iconHandle = AfxGetApp()->LoadIcon(IDI_MOTION_ICON);
    componentInfoList.push_back(componentInfo);

    componentInfo.typeName = AircraftTypeName;
    componentInfo.attributeList = AircraftAttributeList;
    componentInfo.factory = (ComponentFactory)AircraftFactory;
    componentInfo.destroy = (ComponentDestroy)AircraftDestroy;
    componentInfo.iconHandle = AfxGetApp()->LoadIcon(IDI_AIRCRAFT_ICON);
    componentInfoList.push_back(componentInfo);
}
