/**
* @file
* @brief 组件相关函数头文件.
* @author ruoxi
*
* 定义了组件相关函数.
*/

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "rc.h"
#include "interfaces.h"

namespace Component
{
    RC LoadClientComponentDll(LPCWSTR fileName, void **dllHandle);
    RC RegisterClientComponent(void *dllHandle, ComponentInfoList &componentInfoList);
    RC UnloadClientComponentDll(void *dllHandle);

    extern LPCSTR registerClientComponentFuncName;
};

#endif // __COMPONENT_H__
