/**
* @file
* @brief ����ؼ���ͷ�ļ�.
* @author ruoxi
*
* ����������ؼ���.
*/

#ifndef __COMPONENT_CTRL_H__
#define __COMPONENT_CTRL_H__

#include "rect_ctrl.h"

#include "interfaces.h"

class ComponentCtrl : public RectCtrl
{
public:
    ComponentCtrl(IComponent *component, CPoint position = CPoint(0, 0));
    virtual ~ComponentCtrl();

    virtual bool Connect(ModelCtrl *modelCtrl);

public:
    virtual bool SetId(UINT32 id);
    virtual wstring GetTitle();

protected:
    virtual void UpdateAttributeBar();
    virtual void ClearAttributeBar();

protected:
    IComponent *m_Component;
};

#endif // __COMPONENT_CTRL_H__
