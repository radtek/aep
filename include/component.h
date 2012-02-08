/**
* @file
* @brief 组件相关函数头文件.
* @author ruoxi
*
* 定义了组件相关函数.
*/

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "interfaces.h"

namespace Component
{
    // 平台调组件
    typedef void (*RegisterInterfaceTypeFunc)(InterfaceTypeMap &interfaceTypeMap);
    /** @brief 注册接口类型的函数名. */
    extern LPCSTR RegisterInterfaceTypeFuncName;

    typedef void (*RegisterComponentTypeFunc)(ComponentTypeMap &componentTypeMap);
    /** @brief 注册组件类型的函数名. */
    extern LPCSTR RegisterComponentTypeFuncName;

    /*
    typedef bool (*ValidateModelFunc)();
    extern LPCSTR ValidateModelFuncName;

    typedef void (*RunModelFunc)();
    extern LPCSTR RunModelFuncName;
    */

    // 组件及算法调平台
    typedef void (*GetComponentListFunc)(ComponentList &componentList);
    extern GetComponentListFunc GetComponentList;

    typedef void (*RegisterGetComponentListFuncFunc)(GetComponentListFunc getComponentListFunc);
    /** @brief 用来表示组件类型的结构体. */
    extern LPCSTR RegisterGetComponentListFuncFuncName;
};

#endif // __COMPONENT_H__
