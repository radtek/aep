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
Model::Model(ComponentList &componentList)
:
m_SelfOwn(false)
{
}

/**
* 构造一个空模型.
* 此时所有组件必定是由模型自身创建,
* 所以置m_SelfOwn为true.
*/
Model::Model()
:
m_SelfOwn(true)
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
    if (m_SelfOwn)
    {
        for (UINT32 i = 0; i < m_ComponentList.size(); ++i)
        {
            IComponent *component = m_ComponentList[i];
            component->Destroy();
        }
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
    m_SelfOwn = true;

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
        ar >> sourceId
            >> targetId;

        if (sourceValid && targetValid)
        {
            if (!Connect(sourceId, targetId))
            {
                return RC::MODEL_CONNECT_COMPONENT_ERROR;
            }
        }
    }

    return rc;
}

RC Model::Validate()
{
    RC rc;
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
RC Model::Run(wostream &os)
{
    RC rc;

    for (UINT32 ic = 0; ic < m_ComponentList.size(); ++ic)
    {
        IComponent *component = m_ComponentList[ic];
        IParam *iParam = (IParam *)(component->GetInterface(CIID_IPARAM));
        if (iParam != NULL)
        {
            Param *param = iParam->ToParam();
            for (UINT32 ip = 0; ip < param->size(); ++ip)
            {
                double data = (*param)[ip];
                os << data << endl;
            }
        }
    }
    return rc;
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
bool Model::Connect(UINT32 sourceId, UINT32 targetId)
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
        return source->Connect(target);
    }

    return false;
}
