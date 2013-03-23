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
typedef IAlgorithm DrawItem;
typedef vector<DrawItem *> DrawItemList;

class Model
{
public:
    /** @brief Model带参数构造函数. */
    Model(ComponentList &componentList, ConnectorList &connectorList);
    /** @brief Model默认构造函数. */
    Model();
    /** @brief Model析构函数. */
    virtual ~Model();

public:
    /** @brief 从文件中读取模型. */
    RC Load(CArchive &ar);
    /** @brief 验证模型是否有效. */
    virtual RC Analyze();
    /** @brief 运行模型. */
    RC Run();

    virtual RC RunSingleAlgorithm(UINT32 id);

    RC Reset();

    UINT32 GetAlgorithmCount();
    IComponent *GetComponentByName(const wstring &name);

    const DrawItemList &GetDrawItemList();

protected:
    /** @brief 将模型内部的组件相互关联. */
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
    /** @brief 组件列表. */
    ComponentList m_ComponentList;
    ConnectorList m_ConnectorList;

    IGlobalVar *m_GlobalVar;
    AlgorithmList m_AlgorithmList;
    vector<ComponentList> m_InputList;
    vector<ComponentList> m_OutputList;
};

#endif // __MODEL_H__
