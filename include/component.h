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
    typedef void (*GetComponentListFunc)(ComponentList &componentList);
    typedef void (*RegisterComponentFunc)(ComponentInfoList &componentInfoList, GetComponentListFunc getComponentListFunc);

    extern GetComponentListFunc GetComponentList;
    extern LPCSTR RegisterComponentFuncName;
};

#endif // __COMPONENT_H__
