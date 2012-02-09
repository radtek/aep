/**
* @file
* @brief 内部算法组件头文件.
* @author ruoxi
*
* 定义了内部算法类.
*/

#ifndef __INTERNAL_ALGORITHM_H__
#define __INTERNAL_ALGORITHM_H__

#include "interfaces.h"

/**
* @class InternalAlgorithm
* @brief InternalAlgorithm内部算法类.
*
* InternalAlgorithm内部算法类实现了IAlgorithm接口.
* 它用来表示某一个由系统管理员添加的算法,
* 可供所有用户调用.
* 该类被设计为一个内部组件,
* 集成在平台内, 具有通用性.
* 内部算法可以通过构造函数进行配置,
* 能够实现不同的内部算法对象表示不同的算法.
*/
class InternalAlgorithm : public IAlgorithm
{
public:
    /** @brief InternalAlgorithm默认构造函数. */
    InternalAlgorithm();
    /** @brief InternalAlgorithm带参数构造函数. */
    InternalAlgorithm(UINT32 id,
        wstring name,
        wstring dllFileName,
        wstring funcName);
    /** @brief InternalAlgorithm析构函数. */
    virtual ~InternalAlgorithm();

    virtual UINT32 _stdcall GetTypeId();
    virtual void _stdcall Save(CArchive &ar);
    virtual void _stdcall Load(CArchive &ar);
    virtual void _stdcall Destroy();
    virtual void * _stdcall GetInterface(UINT32 iid);
    virtual UINT32 _stdcall GetId();
    virtual void _stdcall SetId(UINT32 id);
    virtual wstring _stdcall GetName();
    virtual void _stdcall SetName(wstring name);
    virtual void _stdcall GetAttributeList(AttributeList &attributeList);
    virtual RC _stdcall GetAttribute(UINT32 aid, void *attr);
    virtual RC _stdcall SetAttribute(UINT32 aid, void *attr);
    virtual bool _stdcall Connect(IComponent *component);

    virtual RC _stdcall Run();

public:
    /** @brief 算法ID. */
    UINT32 m_Id;
    /** @brief 算法名称. */
    wstring m_Name;
    /** @brief 算法DLL文件名. */
    wstring m_DllFileName;
    /** @brief 算法入口函数名称. */
    wstring m_FuncName;

    typedef vector<IParam *> ParamList;
    /** @brief 算法参数列表. */
    ParamList m_ParamList;
    
public:
    /** @brief 内部算法统一的组件ID. */
    static const CCID s_ComponentId = CCID_INTERNAL_ALGORITHM;
    /** @brief 内部算法统一的组件名称. */
    static LPCWSTR s_ComponentName;
};

typedef map<UINT32, InternalAlgorithm> InternalAlgorithmMap;

#endif // __INTERNAL_ALGORITHM_H__
