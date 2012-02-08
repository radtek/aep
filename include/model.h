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
    Model(ComponentList &componentList);
    /** @brief ModelĬ�Ϲ��캯��. */
    Model();
    /** @brief Model��������. */
    virtual ~Model();

public:
    /** @brief ���ļ��ж�ȡģ��. */
    RC Load(CArchive &ar);
    /** @brief ��֤ģ���Ƿ���Ч. */
    RC Validate();
    /** @brief ����ģ��. */
    RC Run(wostream &os);

protected:
    /** @brief ��ģ���ڲ�������໥����. */
    bool Connect(UINT32 sourceId, UINT32 targetId);

private:
    /** @brief ������ʾģ���ڵ�����Ƿ�Ϊģ��������. */
    bool m_SelfOwn;
    /** @brief ����б�. */
    ComponentList m_ComponentList;
};

#endif // __MODEL_H__
