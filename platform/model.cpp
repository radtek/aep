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
Model::Model(ComponentList &componentList)
:
m_SelfOwn(false)
{
}

/**
* ����һ����ģ��.
* ��ʱ��������ض�����ģ��������,
* ������m_SelfOwnΪtrue.
*/
Model::Model()
:
m_SelfOwn(true)
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
