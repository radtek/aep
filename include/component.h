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

namespace Component
{
    RC LoadClientComponentDll(const char *fileName);
    RC RegisterClientComponents();
};

#endif // __COMPONENT_H__
