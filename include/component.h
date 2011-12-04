/**
* @file
* @brief �����غ���ͷ�ļ�.
* @author ruoxi
*
* �����������غ���.
*/

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "interfaces.h"

namespace Component
{
    // ƽ̨�����
    typedef void (*RegisterInterfaceTypeFunc)(InterfaceTypeMap &interfaceTypeMap);
    extern LPCSTR RegisterInterfaceTypeFuncName;

    typedef void (*RegisterComponentTypeFunc)(ComponentTypeMap &componentTypeMap);
    extern LPCSTR RegisterComponentTypeFuncName;

    /*
    typedef bool (*ValidateModelFunc)();
    extern LPCSTR ValidateModelFuncName;

    typedef void (*RunModelFunc)();
    extern LPCSTR RunModelFuncName;
    */

    // ������㷨��ƽ̨
    typedef void (*GetComponentListFunc)(ComponentList &componentList);
    extern GetComponentListFunc GetComponentList;

    typedef void (*RegisterGetComponentListFuncFunc)(GetComponentListFunc getComponentListFunc);
    extern LPCSTR RegisterGetComponentListFuncFuncName;
};

#endif // __COMPONENT_H__
