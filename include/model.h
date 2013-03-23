/**
* @file
* @brief ģ����ͷ�ļ�.
* @author ruoxi
*
* ������ģ����.
*/

#ifndef __MODEL_H__
#define __MODEL_H__

#include "interfaces.h"

/**
* @class Model
* @brief Modelģ����.
*
* Modelģ���������˹���ģ�͵ĸ��ֲ���.
* ��ͨ��һ������б�������ģ��,
* ͬʱ�ܹ����ļ��ж�ȡģ��,
* ��֤ģ���Ƿ���Ч,
* ��֯ģ��������Ľ�����ϵ,
* ���ܹ�����ģ��.
*/
typedef IAlgorithm DrawItem;
typedef vector<DrawItem *> DrawItemList;

class Model
{
public:
    /** @brief Model���������캯��. */
    Model(ComponentList &componentList, ConnectorList &connectorList);
    /** @brief ModelĬ�Ϲ��캯��. */
    Model();
    /** @brief Model��������. */
    virtual ~Model();

public:
    /** @brief ���ļ��ж�ȡģ��. */
    RC Load(CArchive &ar);
    /** @brief ��֤ģ���Ƿ���Ч. */
    virtual RC Analyze();
    /** @brief ����ģ��. */
    RC Run();

    virtual RC RunSingleAlgorithm(UINT32 id);

    RC Reset();

    UINT32 GetAlgorithmCount();
    IComponent *GetComponentByName(const wstring &name);

    const DrawItemList &GetDrawItemList();

protected:
    /** @brief ��ģ���ڲ�������໥����. */
    void Connect(UINT32 sourceId, UINT32 targetId);
    bool Connect(IComponent *source, IComponent *target);
    IGlobalVar *GetGlobalVar();
    IAlgorithm *GetEntryAlgorithm();
    IAlgorithm *GetNextAlgorithm(IAlgorithm *algorithm);
    ComponentList GetInputList(IAlgorithm *algorithm);
    bool CheckInputList(IAlgorithm *algorithm, ComponentList &inputList);
    ComponentList GetOutputList(IAlgorithm *algorithm);
    bool CheckOutputList(IAlgorithm *algorithm, ComponentList &outputList);

protected:
    /** @brief ����б�. */
    ComponentList m_ComponentList;
    ConnectorList m_ConnectorList;

    IGlobalVar *m_GlobalVar;
    AlgorithmList m_AlgorithmList;
    vector<ComponentList> m_InputList;
    vector<ComponentList> m_OutputList;
};

#endif // __MODEL_H__
