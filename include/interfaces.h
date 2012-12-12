/**
* @file
* @brief 接口头文件.
* @author ruoxi
*
* 定义了平台组件的全部接口.
*/

#ifndef __INTERFACES_H__
#define __INTERFACES_H__

#include <vector>
#include <map>
#include "rc.h"
#include <engine.h>
#include <mclmcrrt.h>

using namespace std;

/** @brief 表示内部接口ID的枚举类型. */
enum CIID
{
    CIID_FIRST = 0,
    CIID_IDATA,
    CIID_ICOMPONENT,
    CIID_IPARAM,
    CIID_IALGORITHM,
    CIID_LAST,
};

/** @brief 用于开始声明外部接口ID的宏. */
#define BEGIN_CLIENT_CIID \
    enum CLIENT_CIID \
    { \
        CLIENT_CIID_FIRST = CIID_LAST,

/** @brief 用于结束声明外部接口ID的宏. */
#define END_CLIENT_CIID \
        CLIENT_CIID_LAST, \
    };

/** @brief 表示内部组件ID的枚举类型. */
enum CCID
{
    CCID_FIRST = 0,
    CCID_INTERNAL_ALGORITHM,
    CCID_EXTERNAL_ALGORITHM,
    CCID_LAST,
};

/** @brief 用于开始声明外部组件ID的宏. */
#define BEGIN_CLIENT_CCID \
    enum CLIENT_CCID \
    { \
        CLIENT_CCID_FIRST = CIID_LAST,

/** @brief 用于结束声明外部组件ID的宏. */
#define END_CLIENT_CCID \
        CLIENT_CCID_LAST, \
    };

typedef vector<UINT32> InterfaceList;

/**
* @class InterfaceType
* @brief 用来表示接口类型的结构体.
*/
typedef struct
{
    /** @brief 接口ID. */
    UINT32 InterfaceId;
    /** @brief 接口名称. */
    LPCWSTR InterfaceName;
} InterfaceType;

typedef map<UINT32, InterfaceType> InterfaceTypeMap;

/**
* @class Attribute
* @brief 用来表示属性类型的结构体.
*/
typedef struct
{
    /** @brief 属性ID. */
    UINT32 Id;
    /** @brief 属性名称. */
    wstring Name;
    /** @brief 属性类型. */
    enum AttributeType
    {
        TYPE_UNKNOWN,
        TYPE_INT,
        TYPE_DOUBLE,
        TYPE_STRING,
    } Type;
} Attribute;

typedef vector<Attribute> AttributeList;

/**
* @class IData
* @brief IData数据接口.
*
* 数据接口抽象了组件与组件之间通信的数据流(输入和输出).
*/
struct IData
{
    /** @brief 得到该数据的某一接口. */
    virtual void * _stdcall GetInterface(UINT32 iid) = 0;
};

/**
* @class IComponent
* @brief IComponent组件接口.
*
* 组件接口抽象了平台关于所有组件的一般性操作.
* 对于平台来说, 它所看到的所有组件均是实现了该接口的实例.
* 平台对于所有组件并不区别对待,
* 而只是一般性的调用接口中的操作(即函数).
*/
struct IComponent
{
    // virtual RC _stdcall Config() = 0;
    /** @brief 获得组件类型ID. */
    virtual UINT32 _stdcall GetTypeId() = 0;
    /** @brief 将组件保存至二进制文件. */
    virtual void _stdcall Save(CArchive &ar) = 0;
    /** @brief 从二进制文件中读取组件. */
    virtual void _stdcall Load(CArchive &ar) = 0;
    /** @brief 销毁组件. */
    virtual void _stdcall Destroy() = 0;
    /** @brief 得到该组件的某一接口. */
    virtual void * _stdcall GetInterface(UINT32 iid) = 0;
    /** @brief 获得组件实例ID. */
    virtual UINT32 _stdcall GetId() = 0;
    /** @brief 设置组件实例ID. */
    virtual void _stdcall SetId(UINT32 id) = 0;
    /** @brief 获得组件实例名称. */
    virtual wstring _stdcall GetName() = 0;
    /** @brief 设置组件实例名称. */
    virtual void _stdcall SetName(wstring name) = 0;
    /** @brief 获得组件的属性列表. */
    virtual void _stdcall GetAttributeList(AttributeList &attributeList) = 0;
    /** @brief 获得组件的某一个属性值. */
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr) = 0;
    /** @brief 设置组件的某一个属性值. */
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr) = 0;
    /** @brief 将组件与另一组间相关联. */
    // virtual bool _stdcall Connect(IComponent *component) = 0;
    // virtual bool _stdcall Validate() = 0;

    virtual IComponent * _stdcall Clone() = 0;
    virtual void _stdcall Reset() = 0;
    virtual RC _stdcall Config() = 0;
    virtual RC _stdcall SetInput(IData *input) = 0;
    /** @brief 运行组件. */
    virtual RC _stdcall Run() = 0;
    virtual RC _stdcall GetOutput(IData *&output) = 0;
};

typedef vector<IComponent *> ComponentList;

// typedef mxArray Param;
// typedef mxArray Output;
typedef vector<double> Param;
typedef vector<double> Output;

/**
* @class IParam
* @brief IParam参数接口.
*
* 参数接口继承自组件接口.
* 它抽象了关于参数的一般性操作,
*/
struct IParam : public IComponent
{
    virtual Param * _stdcall ToParam() = 0;
    virtual UINT32 _stdcall GetParamSize() = 0;
    /** @brief 绘制参数曲线. */
    virtual RC _stdcall DrawFigure(Engine *engine) = 0;
};

typedef IComponent *(*ComponentFactory)(void);

/**
* @class ComponentType
* @brief 用来表示组件类型的结构体.
*/
typedef struct
{
    /** @brief 获得组件类型ID. */
    UINT32 TypeId;
    /** @brief 获得组件类型名称. */
    LPCWSTR TypeName;
    /** @brief 获得接口ID. */
    UINT32 InterfaceId;
    // UINT32 *attributeList;
    /** @brief 获得组件的工厂函数. */
    ComponentFactory Factory;
    /** @brief 组件所在DLL的句柄. */
    HINSTANCE DllHandle;
    /** @brief 组件所在DLL的VC工程文件名. */
    LPCWSTR VcprojPath;
    // ComponentDestroy destroy;
    // void *iconHandle;
} ComponentType;

typedef map<UINT32, ComponentType> ComponentTypeMap;

/**
* @class IAlgorithm
* @brief IAlgorithm算法接口.
*
* 算法接口继承自组件接口.
* 它抽象了关于算法的一般性操作,
*/
struct IAlgorithm : public IComponent
{
    virtual bool _stdcall IsEntrance() = 0;
    virtual RC _stdcall InternalRun() = 0;

    virtual RC _stdcall Run();
    virtual UINT64 _stdcall GetNS();
    virtual UINT32 _stdcall GetMemoryUsageKB();
    virtual UINT32 _stdcall GetCpuPercentage();

private:
    virtual void _stdcall BeforeRun();
    virtual void _stdcall AfterRun();
    UINT64 m_NS;
    UINT32 m_MemoryUsageKB;
};

typedef vector<IAlgorithm *> AlgorithmList;

struct Connector
{
    Connector(IComponent *source = NULL, IComponent *target = NULL)
        :
    Source(source), Target(target)
    {}

    IComponent *Source, *Target;
};

typedef vector<Connector> ConnectorList;

class PlatformService
{
public:
    virtual RC DownloadFile(LPCWSTR filePath) = 0;
};

#endif // __INTERFACES_H__
