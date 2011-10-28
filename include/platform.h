/**
* @file
* @brief 平台头文件.
* @author ruoxi
*
* 定义了平台类.
*/

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "rc.h"
#include "interfaces.h"

class Platform
{
public:
    RC LoadComponentDll(LPCWSTR fileName);
    RC RegisterComponent();
    RC UnloadComponentDll();

    ComponentInfoList &GetComponentInfoList();
    ComponentList &GetComponentList();

private:
    ComponentInfoList m_ComponentInfoList;
    ComponentList m_ComponentList;

    HINSTANCE m_DllHandle;
};

#endif // __PLATFORM_H__
