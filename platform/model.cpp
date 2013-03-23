/**
* @file
* @brief ģ����cpp�ļ�.
* @author ruoxi
*
* ʵ����ģ����.
*/

#include "model.h"

#include "platform.h"

/**
* @param componentList ���������캯��.
*
* ͨ��һ������б�������ģ��.
* ��ʱ��������������ⲿ����,
* ������m_SelfOwnΪfalse.
*/
Model::Model(ComponentList &componentList, ConnectorList &connectorList)
{
    for (UINT32 i = 0; i < componentList.size(); ++i)
    {
        IComponent *component = componentList[i]->Clone();
        m_ComponentList.push_back(component);
    }
    for (UINT32 i = 0; i < connectorList.size(); ++i)
    {
        Connector connector = connectorList[i], connectorClone;
        for (UINT32 i = 0; i < componentList.size(); ++i)
        {
            if (connector.Source == componentList[i])
            {
                connectorClone.Source = m_ComponentList[i];
            }
            if (connector.Target == componentList[i])
            {
                connectorClone.Target = m_ComponentList[i];
            }
        }
        if (connectorClone.Source != NULL && connectorClone.Target != NULL)
        {
            m_ConnectorList.push_back(connectorClone);
        }
    }
}

/**
* ����һ����ģ��.
* ��ʱ��������ض�����ģ��������,
* ������m_SelfOwnΪtrue.
*/
Model::Model()
{
}

/**
* ��ģ�����ٵ�ʱ��,
* ���ж�����Ƿ���������.
* ���m_SelfOwn,
* ��Ϊtrue,
* ����Ҫͬʱ�����������.
*/
Model::~Model()
{
    for (UINT32 i = 0; i < m_ComponentList.size(); ++i)
    {
        IComponent *component = m_ComponentList[i];
        component->Destroy();
    }
}

/**
* @param ar ģ�ͱ�����ļ�.
* @return �������.
*
* ���ȴ��ļ��ж��������������,
* Ȼ��������֮��Ĺ�����ϵ,
* ���ҵ���Connect������������й���.
* �����������κ�һ��������ִ���,
* �򷵻ض�Ӧ�Ľ������.
* ���򷵻�OK.
*/
RC Model::Load(CArchive &ar)
{
    RC rc;

    m_ComponentList.clear();

    UINT32 componentListSize = 0;
    ar >> componentListSize;

    for (UINT32 i = 0; i < componentListSize; ++i)
    {
        UINT32 componentId;
        ar >> componentId;

        IComponent *component = NULL;

        if (componentId == CCID_INTERNAL_ALGORITHM)
        {
            UINT32 id;
            ar >> id;
            component = &(Platform::GetInstance().GetInternalAlgorithmMap()[id]);
            component->Load(ar);
        }
        else if (componentId == CCID_EXTERNAL_ALGORITHM)
        {
        }
        else
        {
            component = Platform::GetInstance().GetComponentTypeMap()[componentId].Factory();
            component->Load(ar);
        }

        if (component != NULL)
        {
            m_ComponentList.push_back(component);
        }
        else
        {
            return RC::MODEL_LOAD_COMPONENT_ERROR;
        }
    }

    UINT32 connectorListSize = 0;
    ar >> connectorListSize;

    for (UINT32 i = 0; i < connectorListSize; ++i)
    {
        BOOL sourceValid, targetValid;
        ar >> sourceValid >> targetValid;

        UINT32 sourceId, targetId;
        ar >> sourceId >> targetId;

        if (sourceValid && targetValid)
        {
            Connect(sourceId, targetId);
        }
    }

    return rc;
}

RC Model::Analyze()
{
    RC rc;
    
    // �ҵ���ں���.
    IAlgorithm *algorithm = GetEntryAlgorithm();
    if (algorithm == NULL)
    {
        return RC::MODEL_GET_ENTRY_ALGORITHM_ERROR;
    }

    while (algorithm != NULL)
    {
        ComponentList inputList = GetInputList(algorithm);
        if (!CheckInputList(algorithm, inputList))
        {
            return RC::MODEL_ALGORITHM_INPUT_ERROR;
        }
        ComponentList outputList = GetOutputList(algorithm);
        if (!CheckOutputList(algorithm, outputList))
        {
            return RC::MODEL_ALGORITHM_OUTPUT_ERROR;
        }
        m_AlgorithmList.push_back(algorithm);
        m_InputList.push_back(inputList);
        m_OutputList.push_back(outputList);

        algorithm = GetNextAlgorithm(algorithm);
    }

    return rc;
}

/**
* @param os ���ģ�����н�����ݵ���.
* @return �������.
*
* ��������б�,
* �ҳ����еĲ������.
* �����в�������������ɲ����ĺ���ToParam.
* �������������¼����os��.
* �����������κ�һ��������ִ���,
* �򷵻ض�Ӧ�Ľ������.
* ���򷵻�OK.
*/
RC Model::Run()
{
    RC rc;

    for (UINT32 i = 0; i < m_AlgorithmList.size(); ++i)
    {
        CHECK_RC(RunSingleAlgorithm(i));
    }

    return rc;
}

RC Model::Reset()
{
    RC rc;

    for (UINT32 i = 0; i < m_ComponentList.size(); ++i)
    {
        IComponent *component = m_ComponentList[i];
        component->Reset();
    }

    return rc;
}

UINT32 Model::GetAlgorithmCount()
{
    return m_AlgorithmList.size();
}

const DrawItemList &Model::GetDrawItemList()
{
    return m_AlgorithmList;
}

IComponent *Model::GetComponentByName(const wstring &name)
{
    for (UINT32 i = 0; i < m_ComponentList.size(); ++i)
    {
        IComponent *component = m_ComponentList[i];
        if (component->GetName() == name)
        {
            return component;
        }
    }
    return NULL;
}

/**
* @param sourceId ������ͷ���.
* @param targetId ������β���.
* @return �Ƿ�����ɹ�.
*
* ���ȴ�����б����ҵ�ͷ�����β���.
* ���ҵ�,
* �����ͷ�����Connect��������β���.
* �����Թ���, �򷵻�true,
* ���򷵻�false.
*/
void Model::Connect(UINT32 sourceId, UINT32 targetId)
{
    IComponent *source = NULL, *target = NULL;
    for (UINT32 i = 0; i < m_ComponentList.size(); ++i)
    {
        IComponent *component = m_ComponentList[i];
        if (sourceId == component->GetId())
        {
            source = component;
        }
        if (targetId == component->GetId())
        {
            target = component;
        }
    }

    if (source != NULL &&
        target != NULL)
    {
        Connector connector;
        connector.Source = source;
        connector.Target = target;
        m_ConnectorList.push_back(connector);
    }
}

bool Model::Connect(IComponent *source, IComponent *target)
{
    IData *output = NULL;
    if (OK != source->GetOutput(output))
    {
        return false;
    }
    if (OK != target->SetInput(output))
    {
        return false;
    }
    return true;
}

IGlobalVar *Model::GetGlobalVar()
{
    for (UINT32 i = 0; i < m_ComponentList.size(); ++i)
    {
        IComponent *component = m_ComponentList[i];
        IGlobalVar *globalVar = (IGlobalVar *)component->GetInterface(CIID_IGLOBAL_VAR);
        if (globalVar != NULL)
        {
            return globalVar;
        }
    }

    return NULL;
}

IAlgorithm *Model::GetEntryAlgorithm()
{
    for (UINT32 i = 0; i < m_ComponentList.size(); ++i)
    {
        IComponent *component = m_ComponentList[i];
        IAlgorithm *algorithm = (IAlgorithm *)component->GetInterface(CIID_IALGORITHM);
        if (algorithm != NULL)
        {
            bool hasPrev = false;
            for (UINT32 j = 0; j < m_ConnectorList.size(); ++j)
            {
                Connector connector = m_ConnectorList[j];
                if (connector.Target == component)
                {
                    if (connector.Source->GetInterface(CIID_IALGORITHM) != NULL)
                    {
                        hasPrev = true;
                        break;
                    }
                }
            }
            if (!hasPrev)
            {
                return algorithm;
            }
        }
    }

    return NULL;
}

IAlgorithm *Model::GetNextAlgorithm(IAlgorithm *algorithm)
{
    for (UINT32 i = 0; i < m_ConnectorList.size(); ++i)
    {
        Connector connector = m_ConnectorList[i];
        if (connector.Source == algorithm->GetInterface(CIID_ICOMPONENT))
        {
            if (connector.Target->GetInterface(CIID_IALGORITHM) != NULL)
            {
                return (IAlgorithm *)connector.Target->GetInterface(CIID_IALGORITHM);
            }
        }
    }
    return NULL;
}

ComponentList Model::GetInputList(IAlgorithm *algorithm)
{
    ComponentList inputList;

    for (UINT32 i = 0; i < m_ConnectorList.size(); ++i)
    {
        Connector connector = m_ConnectorList[i];
        if (connector.Target == algorithm->GetInterface(CIID_ICOMPONENT))
        {
            if (connector.Source->GetInterface(CIID_IALGORITHM) == NULL)
            {
                inputList.push_back(connector.Source);
            }
        }
    }

    return inputList;
}

bool Model::CheckInputList(IAlgorithm *algorithm, ComponentList &inputList)
{
    for (UINT32 i = 0; i < inputList.size(); ++i)
    {
        IComponent *source = inputList[i];
        IComponent *target = (IComponent *)algorithm->GetInterface(CIID_ICOMPONENT);
        if (!Connect(source, target))
        {
            return false;
        }
    }
    return true;
}

ComponentList Model::GetOutputList(IAlgorithm *algorithm)
{
    ComponentList outputList;

    for (UINT32 i = 0; i < m_ConnectorList.size(); ++i)
    {
        Connector connector = m_ConnectorList[i];
        if (connector.Source == algorithm->GetInterface(CIID_ICOMPONENT))
        {
            if (connector.Target->GetInterface(CIID_IALGORITHM) == NULL)
            {
                outputList.push_back(connector.Target);
            }
        }
    }

    return outputList;
}

bool Model::CheckOutputList(IAlgorithm *algorithm, ComponentList &outputList)
{
    for (UINT32 i = 0; i < outputList.size(); ++i)
    {
        IComponent *source = (IComponent *)algorithm->GetInterface(CIID_ICOMPONENT);
        IComponent *target = outputList[i];
        if (!Connect(source, target))
        {
            return false;
        }
    }
    return true;
}

RC Model::RunSingleAlgorithm(UINT32 id)
{
    RC rc;

    IAlgorithm *algorithm = m_AlgorithmList[id];
    ComponentList inputList = m_InputList[id];
    for (UINT32 j = 0; j < inputList.size(); ++j)
    {
        IComponent *component = inputList[j];
        CHECK_RC(component->Run());
        if (!Connect(component, (IComponent *)algorithm->GetInterface(CIID_ICOMPONENT)))
        {
            return RC::MODEL_ALGORITHM_INPUT_ERROR;
        }
    }
    CHECK_RC(algorithm->Run());
    ComponentList outputList = m_OutputList[id];
    for (UINT32 j = 0; j < outputList.size(); ++j)
    {
        IComponent *component = outputList[j];
        if (!Connect((IComponent *)algorithm->GetInterface(CIID_ICOMPONENT), component))
        {
            return RC::MODEL_ALGORITHM_OUTPUT_ERROR;
        }
        CHECK_RC(component->Run());
    }
    if (id < m_AlgorithmList.size() - 1)
    {
        IAlgorithm *nextAlgorithm = m_AlgorithmList[id + 1];
        if (!Connect((IComponent *)algorithm->GetInterface(CIID_ICOMPONENT), (IComponent *)nextAlgorithm->GetInterface(CIID_ICOMPONENT)))
        {
            return RC::MODEL_ALGORITHM_OUTPUT_ERROR;
        }
    }

    return rc;
}
