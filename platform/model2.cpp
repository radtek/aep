#include "model2.h"

Model2::Model2()
:
Model()
{
}

Model2::Model2(ComponentList &componentList, ConnectorList &connectorList)
:
Model(componentList, connectorList)
{
}

Model2::~Model2()
{
    for (UINT32 i = 0; i < m_InputTreeList.size(); ++i)
    {
        ComponentNode *inputTree = m_InputTreeList[i];
        DestroyInputTree(inputTree);
    }
    for (UINT32 i = 0; i < m_OutputTreeList.size(); ++i)
    {
        ComponentNode *outputTree = m_OutputTreeList[i];
        DestroyOutputTree(outputTree);
    }
}

RC Model2::Analyze()
{
    RC rc;
    
    // 找到入口函数.
    IAlgorithm *algorithm;
    CHECK_RC(GetEntranceAlgorithm(algorithm));
    if (algorithm == NULL)
    {
        return RC::MODEL_GET_ENTRY_ALGORITHM_ERROR;
    }

    while (algorithm != NULL)
    {
        ComponentNode *inputTree = GetInputTree((IComponent *)(algorithm->GetInterface(CIID_ICOMPONENT)));
        if (!CheckInputTree(inputTree))
        {
            return RC::MODEL_ALGORITHM_INPUT_ERROR;
        }
        ComponentNode *outputTree = GetOutputTree((IComponent *)(algorithm->GetInterface(CIID_ICOMPONENT)));
        if (!CheckOutputTree(outputTree))
        {
            return RC::MODEL_ALGORITHM_OUTPUT_ERROR;
        }
        m_AlgorithmList.push_back(algorithm);
        m_InputTreeList.push_back(inputTree);
        m_OutputTreeList.push_back(outputTree);

        CHECK_RC(GetNextAlgorithm(algorithm, algorithm));
    }

    return rc;
}

RC Model2::RunSingleAlgorithm(UINT32 id)
{
    RC rc;

    IAlgorithm *algorithm = m_AlgorithmList[id];
    ComponentNode *inputTree = m_InputTreeList[id];
    ComponentNode *outputTree = m_OutputTreeList[id];

    for (UINT32 i = 0; i < inputTree->leaf.size(); ++i)
    {
        ComponentNode *node = inputTree->leaf[i];
        CHECK_RC(RunInputTree(node));
        IComponent *component = node->data;
        if (!Connect(component, (IComponent *)algorithm->GetInterface(CIID_ICOMPONENT)))
        {
            return RC::MODEL_ALGORITHM_INPUT_ERROR;
        }
    }

    CHECK_RC(algorithm->Run());

    for (UINT32 i = 0; i < outputTree->leaf.size(); ++i)
    {
        ComponentNode *node = outputTree->leaf[i];
        IComponent *component = node->data;
        if (!Connect((IComponent *)algorithm->GetInterface(CIID_ICOMPONENT), component))
        {
            return RC::MODEL_ALGORITHM_OUTPUT_ERROR;
        }
        CHECK_RC(RunOutputTree(node));
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

RC Model2::GetEntranceAlgorithm(IAlgorithm *&entranceAlgorithm)
{
    RC rc;

    bool found = false;
    for (UINT32 i = 0; i < m_ComponentList.size(); ++i)
    {
        IComponent *component = m_ComponentList[i];
        IAlgorithm *algorithm = (IAlgorithm *)component->GetInterface(CIID_IALGORITHM);
        if (algorithm != NULL)
        {
            if (algorithm->IsEntrance())
            {
                if (found)
                {
                    entranceAlgorithm = NULL;
                    return RC::MODEL_MULTI_ENTRANCE_ALGORITHM_ERROR;
                }
                else
                {
                    entranceAlgorithm = algorithm;
                    found = true;
                }
            }
        }
    }

    if (found)
    {
        return OK;
    }
    else
    {
        return RC::MODEL_NO_ENTRANCE_ALGORITHM_ERROR;
    }
}

RC Model2::GetNextAlgorithm(IAlgorithm *algorithm, IAlgorithm *&nextAlgorithm)
{
    RC rc;

    bool found = false;
    for (UINT32 i = 0; i < m_ConnectorList.size(); ++i)
    {
        Connector connector = m_ConnectorList[i];
        if (connector.Source == algorithm->GetInterface(CIID_ICOMPONENT))
        {
            if (connector.Target->GetInterface(CIID_IALGORITHM) != NULL)
            {
                if (found)
                {
                    nextAlgorithm = NULL;
                    return RC::MODEL_MULTI_NEXT_ALGORITHM_ERROR;
                }
                else
                {
                    nextAlgorithm = (IAlgorithm *)connector.Target->GetInterface(CIID_IALGORITHM);
                    found = true;
                }
            }
        }
    }

    if (!found)
    {
        nextAlgorithm = NULL;
    }

    return OK;
}

ComponentNode *Model2::GetInputTree(IComponent *component)
{
    vector<ComponentNode *> nodes;
    for (UINT32 i = 0; i < m_ConnectorList.size(); ++i)
    {
        Connector connector = m_ConnectorList[i];
        if (connector.Target == component)
        {
            if (connector.Source->GetInterface(CIID_IALGORITHM) == NULL)
            {
                ComponentNode *node = GetInputTree(connector.Source);
                nodes.push_back(node);
            }
        }
    }

    ComponentNode *componentNode = new ComponentNode;
    componentNode->data = component;
    componentNode->leaf = nodes;

    return componentNode;
}

ComponentNode *Model2::GetOutputTree(IComponent *component)
{
    vector<ComponentNode *> nodes;
    for (UINT32 i = 0; i < m_ConnectorList.size(); ++i)
    {
        Connector connector = m_ConnectorList[i];
        if (connector.Source == component)
        {
            if (connector.Target->GetInterface(CIID_IALGORITHM) == NULL)
            {
                ComponentNode *node = GetOutputTree(connector.Target);
                nodes.push_back(node);
            }
        }
    }

    ComponentNode *componentNode = new ComponentNode;
    componentNode->data = component;
    componentNode->leaf = nodes;

    return componentNode;
}

bool Model2::CheckInputTree(ComponentNode *inputTree)
{
    for (UINT32 i = 0; i < inputTree->leaf.size(); ++i)
    {
        if (!CheckInputTree(inputTree->leaf[i]))
        {
            return false;
        }
        IComponent *source = inputTree->leaf[i]->data;
        IComponent *target = inputTree->data;
        if (!Connect(source, target))
        {
            return false;
        }
    }
    return true;
}

bool Model2::CheckOutputTree(ComponentNode *outputTree)
{
    for (UINT32 i = 0; i < outputTree->leaf.size(); ++i)
    {
        if (!CheckOutputTree(outputTree->leaf[i]))
        {
            return false;
        }
        IComponent *source = outputTree->data;
        IComponent *target = outputTree->leaf[i]->data;
        if (!Connect(source, target))
        {
            return false;
        }
    }
    return true;
}

RC Model2::RunInputTree(ComponentNode *inputTree)
{
    // 从左到右的后续遍历
    RC rc;

    IComponent *target = inputTree->data;
    for (UINT32 i = 0; i < inputTree->leaf.size(); ++i)
    {
        ComponentNode *node = inputTree->leaf[i];
        CHECK_RC(RunInputTree(node));
        IComponent *source = node->data;
        if (!Connect(source, target))
        {
            return RC::MODEL_ALGORITHM_INPUT_ERROR;
        }
    }
    CHECK_RC(target->Run());

    return OK;
}

RC Model2::RunOutputTree(ComponentNode *outputTree)
{
    // 从左到右的前序遍历
    RC rc;

    IComponent *source = outputTree->data;
    CHECK_RC(source->Run(false));
    for (UINT32 i = 0; i < outputTree->leaf.size(); ++i)
    {
        ComponentNode *node = outputTree->leaf[i];
        IComponent *target = node->data;
        if (!Connect(source, target))
        {
            return RC::MODEL_ALGORITHM_OUTPUT_ERROR;
        }
        CHECK_RC(RunOutputTree(node));
    }

    return OK;
}

void Model2::DestroyInputTree(ComponentNode *inputTree)
{
    for (UINT32 i = 0; i < inputTree->leaf.size(); ++i)
    {
        ComponentNode *node = inputTree->leaf[i];
        DestroyInputTree(node);
    }
    delete inputTree;
}

void Model2::DestroyOutputTree(ComponentNode *outputTree)
{
    for (UINT32 i = 0; i < outputTree->leaf.size(); ++i)
    {
        ComponentNode *node = outputTree->leaf[i];
        DestroyOutputTree(node);
    }
    delete outputTree;
}
