/**
* @file
* @brief �ӿ�ͷ�ļ�.
* @author ruoxi
*
* ������ƽ̨�е�ȫ���ӿ�.
*/

#ifndef __INTERFACES_H__
#define __INTERFACES_H__

#include <vector>
#include "rc.h"
#include <mclmcrrt.h>

using namespace std;

// ������ֽӿ�
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
    UINT32 interfaceId;
    LPCWSTR interfaceName;
} InterfaceInfo;

typedef vector<InterfaceInfo> InterfaceInfoList;

interface IComponent
{
    // virtual RC _stdcall Config() = 0;
    virtual void _stdcall Destroy() = 0;
    virtual void * _stdcall GetInterface(UINT32 iid) = 0;
    virtual UINT32 _stdcall GetId() = 0;
    virtual void _stdcall SetId(UINT32 id) = 0;
    virtual wstring _stdcall GetName() = 0;
    virtual void _stdcall SetName(wstring name) = 0;
    virtual RC _stdcall GetAttribute(UINT32 aid, void **attr) = 0;
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
typedef void (*ComponentDestroy)(IComponent *);

typedef struct
{
    UINT32 componentId;
    LPCWSTR componentName;
    UINT32 interfaceId;
    // UINT32 *attributeList;
    ComponentFactory factory;
    // ComponentDestroy destroy;
    // void *iconHandle;
} ComponentInfo;

typedef vector<ComponentInfo> ComponentInfoList;

#endif // __INTERFACES_H__
