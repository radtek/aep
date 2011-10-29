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
    typedef void (*RegisterComponentInfoFunc)(ComponentInfoList &componentInfoList);
    extern LPCSTR RegisterComponentInfoFuncName;

    typedef bool (*ValidateModelFunc)();
    extern LPCSTR ValidateModelFuncName;

    typedef void (*RunModelFunc)();
    extern LPCSTR RunModelFuncName;

    // 平台调算法
    typedef void (*RegisterAlgorithmFunc)(AlgorithmList &algorithmList);
    extern LPCSTR RegisterAlgorithmFuncName;

    // 组件及算法调平台
    typedef void (*GetComponentListFunc)(ComponentList &componentList);
    extern GetComponentListFunc GetComponentList;

    typedef void (*RegisterGetComponentListFuncFunc)(GetComponentListFunc getComponentListFunc);
    extern LPCSTR RegisterGetComponentListFuncFuncName;
};

#endif // __COMPONENT_H__
