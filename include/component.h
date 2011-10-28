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
    typedef void (*GetComponentListFunc)(ComponentList &componentList);
    typedef void (*RegisterComponentFunc)(ComponentInfoList &componentInfoList, GetComponentListFunc getComponentListFunc);

    extern GetComponentListFunc GetComponentList;
    extern LPCSTR RegisterComponentFuncName;
};

#endif // __COMPONENT_H__
