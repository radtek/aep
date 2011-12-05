/**
* @file
* @brief 接口头文件.
* @author ruoxi
*
* 定义了平台中的全部接口.
*/

#ifndef __INTERFACES_H__
#define __INTERFACES_H__

#include <vector>
#include <map>
#include "rc.h"
#include <mclmcrrt.h>

using namespace std;

// 组件部分接口
enum CIID
{
    CIID_FIRST = 0,
    CIID_ICOMPONENT,
    CIID_IPARAM,
    CIID_LAST,
};

#define BEGIN_CLIENT_CIID \
    enum CLIENT_CIID \
    { \
        CLIENT_CIID_First = CIID_LAST,

#define END_CLIENT_CIID \
        CLIENT_CIID_LAST, \
    };

typedef vector<UINT32> InterfaceList;

typedef struct
{
    UINT32 InterfaceId;
    LPCWSTR InterfaceName;
} InterfaceType;

typedef map<UINT32, InterfaceType> InterfaceTypeMap;

typedef struct
{
    UINT32 Id;
    LPCWSTR Name;
    enum AttributeType
    {
        TYPE_UNKNOWN,
        TYPE_INT,
        TYPE_DOUBLE,
        TYPE_STRING,
    } Type;
} Attribute;

typedef vector<Attribute> AttributeList;

interface IComponent
{
    // virtual RC _stdcall Config() = 0;
    virtual UINT32 _stdcall GetTypeId() = 0;
    virtual void _stdcall Destroy() = 0;
    virtual void * _stdcall GetInterface(UINT32 iid) = 0;
    virtual UINT32 _stdcall GetId() = 0;
    virtual void _stdcall SetId(UINT32 id) = 0;
    virtual wstring _stdcall GetName() = 0;
    virtual void _stdcall SetName(wstring name) = 0;
    virtual void _stdcall GetAttributeList(AttributeList &attributeList) = 0;
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr) = 0;
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr) = 0;
    virtual bool _stdcall Connect(IComponent *component) = 0;
    // virtual bool _stdcall Validate() = 0;
};

typedef vector<IComponent *> ComponentList;

typedef mxArray Param;
typedef mxArray Output;

interface IParam : public IComponent
{
    virtual Param * _stdcall ToParam() = 0;
    virtual UINT32 _stdcall GetParamSize() = 0;
};

typedef IComponent *(*ComponentFactory)(void);

typedef struct
{
    UINT32 TypeId;
    LPCWSTR TypeName;
    UINT32 InterfaceId;
    // UINT32 *attributeList;
    ComponentFactory Factory;
    // ComponentDestroy destroy;
    // void *iconHandle;
} ComponentType;

typedef map<UINT32, ComponentType> ComponentTypeMap;

#endif // __INTERFACES_H__
