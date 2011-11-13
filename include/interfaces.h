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
    LPCWSTR typeName;
    UINT32 *attributeList;
    ComponentFactory factory;
    ComponentDestroy destroy;
    void *iconHandle;
} ComponentInfo;

typedef vector<ComponentInfo> ComponentInfoList;

#endif // __INTERFACES_H__
