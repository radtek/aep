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

namespace Component
{
    RC LoadClientComponentDll(const char *fileName);
    RC RegisterClientComponents();
};

#endif // __COMPONENT_H__
