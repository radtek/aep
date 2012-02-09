/**
* @file
* @brief �ڲ��㷨���ͷ�ļ�.
* @author ruoxi
*
* �������ڲ��㷨��.
*/

#ifndef __INTERNAL_ALGORITHM_H__
#define __INTERNAL_ALGORITHM_H__

#include "interfaces.h"

/**
* @class InternalAlgorithm
* @brief InternalAlgorithm�ڲ��㷨��.
*
* InternalAlgorithm�ڲ��㷨��ʵ����IAlgorithm�ӿ�.
* ��������ʾĳһ����ϵͳ����Ա��ӵ��㷨,
* �ɹ������û�����.
* ���౻���Ϊһ���ڲ����,
* ������ƽ̨��, ����ͨ����.
* �ڲ��㷨����ͨ�����캯����������,
* �ܹ�ʵ�ֲ�ͬ���ڲ��㷨�����ʾ��ͬ���㷨.
*/
class InternalAlgorithm : public IAlgorithm
{
public:
    /** @brief InternalAlgorithmĬ�Ϲ��캯��. */
    InternalAlgorithm();
    /** @brief InternalAlgorithm���������캯��. */
    InternalAlgorithm(UINT32 id,
        wstring name,
        wstring dllFileName,
        wstring funcName);
    /** @brief InternalAlgorithm��������. */
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
    /** @brief �㷨ID. */
    UINT32 m_Id;
    /** @brief �㷨����. */
    wstring m_Name;
    /** @brief �㷨DLL�ļ���. */
    wstring m_DllFileName;
    /** @brief �㷨��ں�������. */
    wstring m_FuncName;

    typedef vector<IParam *> ParamList;
    /** @brief �㷨�����б�. */
    ParamList m_ParamList;
    
public:
    /** @brief �ڲ��㷨ͳһ�����ID. */
    static const CCID s_ComponentId = CCID_INTERNAL_ALGORITHM;
    /** @brief �ڲ��㷨ͳһ���������. */
    static LPCWSTR s_ComponentName;
};

typedef map<UINT32, InternalAlgorithm> InternalAlgorithmMap;

#endif // __INTERNAL_ALGORITHM_H__
