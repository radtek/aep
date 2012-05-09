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
    RC Analyze();
    /** @brief ����ģ��. */
    RC Run();

protected:
    /** @brief ��ģ���ڲ�������໥����. */
    void Connect(UINT32 sourceId, UINT32 targetId);
    bool Connect(IComponent *source, IComponent *target);
    IAlgorithm *GetEntryAlgorithm();
    IAlgorithm *GetNextAlgorithm(IAlgorithm *algorithm);
    ComponentList GetInputList(IAlgorithm *algorithm);
    bool CheckInputList(IAlgorithm *algorithm, ComponentList &inputList);
    ComponentList GetOutputList(IAlgorithm *algorithm);
    bool CheckOutputList(IAlgorithm *algorithm, ComponentList &outputList);

private:
    /** @brief ����б�. */
    ComponentList m_ComponentList;
    ConnectorList m_ConnectorList;
    AlgorithmList m_AlgorithmList;
    vector<ComponentList> m_InputList;
    vector<ComponentList> m_OutputList;
};

#endif // __MODEL_H__
