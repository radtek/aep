/**
* @file
* @brief �����غ���cpp�ļ�.
* @author ruoxi
*
* ʵ���������غ���.
*/

#include "component.h"

LPCSTR Component::RegisterComponentInfoFuncName = "RegisterComponentInfo";

LPCSTR Component::ValidateModelFuncName = "ValidateModel";

LPCSTR Component::RunModelFuncName = "RunModel";

LPCSTR Component::RegisterAlgorithmFuncName = "RegisterAlgorithm";

Component::GetComponentListFunc Component::GetComponentList;

LPCSTR Component::RegisterGetComponentListFuncFuncName = "RegisterGetComponentListFunc";
