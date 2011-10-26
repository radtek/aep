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
    CIID_IALGORITHM,
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
    virtual RC _stdcall GetInterface(UINT32 iid, void **iface) = 0;
    virtual RC _stdcall GetAttribute(UINT32 aid, void **attr) = 0;
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr) = 0;
    // virtual RC _stdcall Validate() = 0;
};

interface IAlgorithm : IComponent
{
    virtual RC _stdcall Run() = 0;
};

typedef IComponent *(*ComponentFactory)(void);

struct ComponentInfo
{
    const char *typeName;
    UINT32 *attributeList;
    ComponentFactory factory;
};

#endif // __INTERFACES_H__
