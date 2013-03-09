/**
* @file
* @brief 模型类头文件.
* @author ruoxi
*
* 定义了模型类.
*/

#ifndef __MODEL_2_H__
#define __MODEL_2_H__

#include "model.h"
#include "tcp_socket.h"

struct ComponentNode
{
    IComponent *data;
    vector<ComponentNode *> leaf;
};

class Model2 : public Model
{
public:
    Model2(ComponentList &componentList, ConnectorList &connectorList);

    Model2();

    virtual ~Model2();

    virtual RC Analyze();

    virtual RC RunSingleAlgorithm(UINT32 id);

protected:
    virtual RC GetEntranceAlgorithm(IAlgorithm *&entranceAlgorithm);
    virtual RC GetNextAlgorithm(IAlgorithm *algorithm, IAlgorithm *&nextAlgorithm);

    ComponentNode *GetInputTree(IComponent *component);
    ComponentNode *GetOutputTree(IComponent *component);
    bool CheckInputTree(ComponentNode *inputTree);
    bool CheckOutputTree(ComponentNode *outputTree);
    RC RunInputTree(ComponentNode *inputTree);
    RC RunOutputTree(ComponentNode *outputTree);
    void DestroyInputTree(ComponentNode *inputTree);
    void DestroyOutputTree(ComponentNode *outputTree);

private:

    vector<ComponentNode *> m_InputTreeList;
    vector<ComponentNode *> m_OutputTreeList;
};

#endif // __MODEL_2_H__
