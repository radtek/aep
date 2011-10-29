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
#include <vector>
#include "rc.h"

using namespace std;

// 组件部分接口
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

interface IComponent;

typedef vector<IComponent *> ComponentList;

interface IComponent
{
    virtual RC _stdcall Config() = 0;
    virtual RC _stdcall Destroy() = 0;
    virtual RC _stdcall GetInterface(UINT32 iid, void **iface) = 0;
    virtual RC _stdcall GetName(LPWSTR *name) = 0;
    virtual RC _stdcall GetAttribute(UINT32 aid, void **attr) = 0;
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr) = 0;
    virtual bool _stdcall Validate() = 0;
};

typedef IComponent *(*ComponentFactory)(void);
typedef void (*ComponentDestroy)(IComponent *);

typedef struct
{
    LPCWSTR typeName;
    UINT32 *attributeList;
    ComponentFactory factory;
    ComponentDestroy destroy;
    void *iconHandle;
} ComponentInfo;

typedef vector<ComponentInfo> ComponentInfoList;

// 算法部分接口
interface IAlgorithm;

typedef vector<IAlgorithm *> AlgorithmList;

interface IAlgorithm
{
    virtual RC _stdcall GetName(LPWSTR *name) = 0;
    virtual RC _stdcall Run() = 0;
};

#endif // __INTERFACES_H__
