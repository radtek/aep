/**
* @file
* @brief �ӿ�ͷ�ļ�.
* @author ruoxi
*
* ������ƽ̨�����ȫ���ӿ�.
*/

#ifndef __INTERFACES_H__
#define __INTERFACES_H__

#include <vector>
#include <map>
#include "rc.h"
#include <engine.h>
#include <mclmcrrt.h>

using namespace std;

/** @brief ��ʾ�ڲ��ӿ�ID��ö������. */
enum CIID
{
    CIID_FIRST = 0,
    CIID_IDATA,
    CIID_ICOMPONENT,
    CIID_IPARAM,
    CIID_IALGORITHM,
    CIID_LAST,
};

/** @brief ���ڿ�ʼ�����ⲿ�ӿ�ID�ĺ�. */
#define BEGIN_CLIENT_CIID \
    enum CLIENT_CIID \
    { \
        CLIENT_CIID_FIRST = CIID_LAST,

/** @brief ���ڽ��������ⲿ�ӿ�ID�ĺ�. */
#define END_CLIENT_CIID \
        CLIENT_CIID_LAST, \
    };

/** @brief ��ʾ�ڲ����ID��ö������. */
enum CCID
{
    CCID_FIRST = 0,
    CCID_INTERNAL_ALGORITHM,
    CCID_EXTERNAL_ALGORITHM,
    CCID_LAST,
};

/** @brief ���ڿ�ʼ�����ⲿ���ID�ĺ�. */
#define BEGIN_CLIENT_CCID \
    enum CLIENT_CCID \
    { \
        CLIENT_CCID_FIRST = CIID_LAST,

/** @brief ���ڽ��������ⲿ���ID�ĺ�. */
#define END_CLIENT_CCID \
        CLIENT_CCID_LAST, \
    };

typedef vector<UINT32> InterfaceList;

/**
* @class InterfaceType
* @brief ������ʾ�ӿ����͵Ľṹ��.
*/
typedef struct
{
    /** @brief �ӿ�ID. */
    UINT32 InterfaceId;
    /** @brief �ӿ�����. */
    LPCWSTR InterfaceName;
} InterfaceType;

typedef map<UINT32, InterfaceType> InterfaceTypeMap;

/**
* @class Attribute
* @brief ������ʾ�������͵Ľṹ��.
*/
typedef struct
{
    /** @brief ����ID. */
    UINT32 Id;
    /** @brief ��������. */
    wstring Name;
    /** @brief ��������. */
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
* @brief IData���ݽӿ�.
*
* ���ݽӿڳ�������������֮��ͨ�ŵ�������(��������).
*/
struct IData
{
    /** @brief �õ������ݵ�ĳһ�ӿ�. */
    virtual void * _stdcall GetInterface(UINT32 iid) = 0;
};

/**
* @class IComponent
* @brief IComponent����ӿ�.
*
* ����ӿڳ�����ƽ̨�������������һ���Բ���.
* ����ƽ̨��˵, ���������������������ʵ���˸ýӿڵ�ʵ��.
* ƽ̨�������������������Դ�,
* ��ֻ��һ���Եĵ��ýӿ��еĲ���(������).
*/
struct IComponent
{
    // virtual RC _stdcall Config() = 0;
    /** @brief ����������ID. */
    virtual UINT32 _stdcall GetTypeId() = 0;
    /** @brief ������������������ļ�. */
    virtual void _stdcall Save(CArchive &ar) = 0;
    /** @brief �Ӷ������ļ��ж�ȡ���. */
    virtual void _stdcall Load(CArchive &ar) = 0;
    /** @brief �������. */
    virtual void _stdcall Destroy() = 0;
    /** @brief �õ��������ĳһ�ӿ�. */
    virtual void * _stdcall GetInterface(UINT32 iid) = 0;
    /** @brief ������ʵ��ID. */
    virtual UINT32 _stdcall GetId() = 0;
    /** @brief �������ʵ��ID. */
    virtual void _stdcall SetId(UINT32 id) = 0;
    /** @brief ������ʵ������. */
    virtual wstring _stdcall GetName() = 0;
    /** @brief �������ʵ������. */
    virtual void _stdcall SetName(wstring name) = 0;
    /** @brief �������������б�. */
    virtual void _stdcall GetAttributeList(AttributeList &attributeList) = 0;
    /** @brief ��������ĳһ������ֵ. */
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr) = 0;
    /** @brief ���������ĳһ������ֵ. */
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr) = 0;
    /** @brief ���������һ��������. */
    // virtual bool _stdcall Connect(IComponent *component) = 0;
    // virtual bool _stdcall Validate() = 0;

    virtual IComponent * _stdcall Clone() = 0;
    virtual void _stdcall Reset() = 0;
    virtual RC _stdcall Config() = 0;
    virtual RC _stdcall SetInput(IData *input) = 0;
    /** @brief �������. */
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
* @brief IParam�����ӿ�.
*
* �����ӿڼ̳�������ӿ�.
* �������˹��ڲ�����һ���Բ���,
*/
struct IParam : public IComponent
{
    virtual Param * _stdcall ToParam() = 0;
    virtual UINT32 _stdcall GetParamSize() = 0;
    /** @brief ���Ʋ�������. */
    virtual RC _stdcall DrawFigure(Engine *engine) = 0;
};

typedef IComponent *(*ComponentFactory)(void);

/**
* @class ComponentType
* @brief ������ʾ������͵Ľṹ��.
*/
typedef struct
{
    /** @brief ����������ID. */
    UINT32 TypeId;
    /** @brief ��������������. */
    LPCWSTR TypeName;
    /** @brief ��ýӿ�ID. */
    UINT32 InterfaceId;
    // UINT32 *attributeList;
    /** @brief �������Ĺ�������. */
    ComponentFactory Factory;
    /** @brief �������DLL�ľ��. */
    HINSTANCE DllHandle;
    /** @brief �������DLL��VC�����ļ���. */
    LPCWSTR VcprojPath;
    // ComponentDestroy destroy;
    // void *iconHandle;
} ComponentType;

typedef map<UINT32, ComponentType> ComponentTypeMap;

/**
* @class IAlgorithm
* @brief IAlgorithm�㷨�ӿ�.
*
* �㷨�ӿڼ̳�������ӿ�.
* �������˹����㷨��һ���Բ���,
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
