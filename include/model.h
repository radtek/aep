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

class Model
{
public:
    Model(ComponentList &componentList);
    Model();
    virtual ~Model();

public:
    RC Load(CArchive &ar);
    RC Validate();
    RC Run(wostream &os);

protected:
    bool Connect(UINT32 sourceId, UINT32 targetId);

private:
    bool m_SelfOwn;
    ComponentList m_ComponentList;
};

#endif // __MODEL_H__
