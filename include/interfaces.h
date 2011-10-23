/**
* @file
* @brief 接口头文件.
* @author ruoxi
*
* 定义了平台中的全部接口.
*/

#ifndef __INTERFACES_H__
#define __INTERFACES_H__

#include <objbase.h>
#include "rc.h"

enum CIID
{
    CIID_FIRST = 0,
    CIID_ICOMPONENT,
    CIID_LAST,
};

#define BEGIN_CLIENT_CIID \
    enum CLIENT_CIID \
    { \
        CLIENT_CIID_First = CIID_LAST,

#define END_CLIENT_CIID \
        CLIENT_CIID_LAST, \
    };

interface IComponent
{
    virtual RC _stdcall QueryInterface(UINT32 iid, void **ppi) = 0;
};

#endif // __INTERFACES_H__
