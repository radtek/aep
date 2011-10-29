#include "component.h"
#include "uniform_linear_motion.h"
#include "acceleration_linear_motion.h"
#include "aircraft.h"
#include "white_noise.h"

#include "model_run_dlg.h"

#include "resource.h"

#include "stdafx.h"

extern "C" __declspec(dllexport) void RegisterComponentInfo(ComponentInfoList &componentInfoList)
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

    componentInfo.typeName = WhiteNoise::WhiteNoiseTypeName;
    componentInfo.attributeList = NULL;
    componentInfo.factory = (ComponentFactory)WhiteNoise::WhiteNoiseFactory;
    componentInfo.destroy = NULL;
    componentInfo.iconHandle = AfxGetApp()->LoadIcon(IDI_NOISE_ICON);
    componentInfoList.push_back(componentInfo);
}

extern "C" __declspec(dllexport) void RegisterGetComponentListFunc(Component::GetComponentListFunc getComponentListFunc)
{
    Component::GetComponentList = getComponentListFunc;
}

Aircraft *me = NULL, *enemy = NULL;
IAircraft *iMe = NULL, *iEnemy = NULL;

extern "C" __declspec(dllexport) bool ValidateModel()
{
    ComponentList componentList;
    Component::GetComponentList(componentList);

    for (UINT32 i = 0; i < componentList.size(); ++i)
    {
        IComponent *component = componentList[i];
        LPWSTR name;
        component->GetName(&name);
        if (CString(TEXT("我机")) == CString(name))
        {
            if (OK != component->GetInterface(CLIENT_CIID_AIRCRAFT, (void **)&iMe))
            {
                MessageBox(NULL, TEXT("我机非飞行器"), TEXT("错误"), MB_OK); 
                return false;
            }
            if (!component->Validate())
            {
                MessageBox(NULL, TEXT("我机状态非法"), TEXT("错误"), MB_OK); 
                return false;
            }
            me = (Aircraft *)component;
        }
        else if (CString(TEXT("敌机")) == CString(name))
        {
            if (OK != component->GetInterface(CLIENT_CIID_AIRCRAFT, (void **)&iEnemy))
            {
                MessageBox(NULL, TEXT("敌机非飞行器"), TEXT("错误"), MB_OK); 
                return false;
            }
            if (!component->Validate())
            {
                MessageBox(NULL, TEXT("敌机状态非法"), TEXT("错误"), MB_OK); 
                return false;
            }
            enemy = (Aircraft *)component;
        }
    }

    if (!me)
    {
        MessageBox(NULL, TEXT("缺少我机"), TEXT("错误"), MB_OK); 
        return false;
    }

    if (!enemy)
    {
        MessageBox(NULL, TEXT("缺少敌机"), TEXT("错误"), MB_OK); 
        return false;
    }

    return true;
}

extern "C" __declspec(dllexport) void RunModel()
{
    // AFX_MANAGE_STATE(AfxGetStaticModuleState());
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CModelRunDlg dlg;
    dlg.DoModal();
}
