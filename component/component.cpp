/**
* @file
* @brief 组件相关函数cpp文件.
* @author ruoxi
*
* 实现了组件相关函数.
*/

#include "component.h"

LPCSTR Component::RegisterComponentInfoFuncName = "RegisterComponentInfo";

LPCSTR Component::ValidateModelFuncName = "ValidateModel";

LPCSTR Component::RunModelFuncName = "RunModel";

Component::GetComponentListFunc Component::GetComponentList;

LPCSTR Component::RegisterGetComponentListFuncFuncName = "RegisterGetComponentListFunc";
