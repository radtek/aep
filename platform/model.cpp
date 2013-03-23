/**
* @file
* @brief 模型类cpp文件.
* @author ruoxi
*
* 实现了模型类.
*/

#include "model.h"

#include "platform.h"

/**
* @param componentList 带参数构造函数.
*
* 通过一个组件列表来构造模型.
* 此时所有组件都是由外部创建,
* 所以置m_SelfOwn为false.
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
* 构造一个空模型.
* 此时所有组件必定是由模型自身创建,
* 所以置m_SelfOwn为true.
*/
Model::Model()
{
}

/**
* 在模型销毁的时候,
* 需判断组件是否由自身创建.
* 检查m_SelfOwn,
* 若为true,
* 则需要同时销毁所有组件.
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
* @param ar 模型保存的文件.
* @return 结果代码.
*
* 首先从文件中读入所有组件数据,
* 然后读入组件之间的关联关系,
* 并且调用Connect函数对组件进行关联.
* 整个过程中任何一个步骤出现错误,
* 则返回对应的结果代码.
* 否则返回OK.
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
    
    // 找到入口函数.
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
* @param os 存放模型运行结果数据的流.
* @return 结果代码.
*
* 遍历组件列表,
* 找出其中的参数组件.
* 对所有参数组件调用生成参数的函数ToParam.
* 并将参数结果记录到流os中.
* 整个过程中任何一个步骤出现错误,
* 则返回对应的结果代码.
* 否则返回OK.
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
* @param sourceId 关联的头组件.
* @param targetId 关联的尾组件.
* @return 是否关联成功.
*
* 首先从组件列表中找到头组件和尾组件.
* 若找到,
* 则调用头组件的Connect函数关联尾组件.
* 若可以关联, 则返回true,
* 否则返回false.
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
