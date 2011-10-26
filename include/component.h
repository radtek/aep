/**
* @file
* @brief �����غ���ͷ�ļ�.
* @author ruoxi
*
* �����������غ���.
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
