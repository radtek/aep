/**
* @file
* @brief 模型类头文件.
* @author ruoxi
*
* 定义了模型类.
*/

#ifndef __MODEL_H__
#define __MODEL_H__

#include "interfaces.h"

/**
* @class Model
* @brief Model模型类.
*
* Model模型类抽象出了关于模型的各种操作.
* 他通过一个组件列表来创建模型,
* 同时能够从文件中读取模型,
* 验证模型是否有效,
* 组织模型中组件的交互关系,
* 还能够运行模型.
*/
class Model
{
public:
    /** @brief Model带参数构造函数. */
    Model(ComponentList &componentList);
    /** @brief Model默认构造函数. */
    Model();
    /** @brief Model析构函数. */
    virtual ~Model();

public:
    /** @brief 从文件中读取模型. */
    RC Load(CArchive &ar);
    /** @brief 验证模型是否有效. */
    RC Validate();
    /** @brief 运行模型. */
    RC Run(wostream &os);

protected:
    /** @brief 将模型内部的组件相互关联. */
    bool Connect(UINT32 sourceId, UINT32 targetId);

private:
    /** @brief 用来表示模型内的组件是否为模型自身创建. */
    bool m_SelfOwn;
    /** @brief 组件列表. */
    ComponentList m_ComponentList;
};

#endif // __MODEL_H__
