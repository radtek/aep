/**
* @file
* @brief 内部算法组件头文件.
* @author ruoxi
*
* 定义了内部算法组件类.
*/

#ifndef __INTERNAL_ALGORITHM_H__
#define __INTERNAL_ALGORITHM_H__

#include "interfaces.h"

class InternalAlgorithm : public IAlgorithm
{
public:
    InternalAlgorithm();
    InternalAlgorithm(UINT32 algorithmId,
        wstring name,
        wstring dllFileName,
        wstring funcName);
    virtual ~InternalAlgorithm();

    virtual UINT32 _stdcall GetTypeId();
    virtual void Save(CArchive &ar);
    virtual void Load(CArchive &ar);
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

    virtual UINT32 _stdcall GetAlgorithmId();
    virtual void _stdcall SetAlgorithmId(UINT32 algorithmId);
    virtual RC _stdcall Run();

public:
    /** @brief 组件ID. */
    UINT32 m_Id;
    /** @brief 算法名称. */
    wstring m_Name;
    /** @brief 算法DLL文件名. */
    wstring m_DllFileName;
    /** @brief 算法入口函数名称. */
    wstring m_FuncName;

    /** @brief 算法ID. */
    UINT32 m_AlgorithmId;

    typedef vector<IParam *> ParamList;
    ParamList m_ParamList;
    
public:
    static const CCID s_ComponentId = CCID_INTERNAL_ALGORITHM;
    static LPCWSTR s_ComponentName;
};

typedef map<UINT32, InternalAlgorithm> InternalAlgorithmMap;

#endif // __INTERNAL_ALGORITHM_H__
