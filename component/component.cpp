/**
* @file
* @brief 组件相关函数cpp文件.
* @author ruoxi
*
* 实现了组件相关函数.
*/

#include "component.h"

LPCSTR Component::registerClientComponentFuncName = "RegisterClientComponent";

static void ErrorExit(LPTSTR lpszFunction);

RC Component::LoadClientComponentDll(LPCWSTR fileName, void **dllHandle)
{
    *dllHandle = LoadLibrary(fileName);

    if (!*dllHandle)
    {
        return RC::COMPONENT_LOADDLL_ERROR;
    }

    return OK;
}

RC Component::RegisterClientComponent(void *dllHandle, ComponentInfoList &componentInfoList)
{
    RC rc;

    typedef void (*RegisterClientComponentFunc)(ComponentInfoList &componentInfoList);
    RegisterClientComponentFunc func = (RegisterClientComponentFunc)GetProcAddress((HMODULE)dllHandle, registerClientComponentFuncName);

    if (!func)
    {
        return RC::COMPONENT_REGISTERCLIENTCOMPONENT_ERROR;
    }

    func(componentInfoList);

    return rc;
}

RC Component::UnloadClientComponentDll(void *dllHandle)
{
    FreeLibrary((HMODULE)dllHandle);
    return OK;
}
