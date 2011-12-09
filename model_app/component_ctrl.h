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
    ComponentCtrl(IComponent *component = NULL, CPoint position = CPoint(0, 0));
    virtual ~ComponentCtrl();
 
    virtual void Save(CArchive &ar);
    virtual void Load(CArchive &ar);

    virtual bool Connect(ModelCtrl *modelCtrl);

public:
    virtual bool SetId(UINT32 id);
    virtual wstring GetTitle();

protected:
    virtual void UpdateAttributeBar();
    virtual void ClearAttributeBar();

protected:
    IComponent *m_Component;

public:
    static const UINT32 s_ModelCtrlId = 0;
};

#endif // __COMPONENT_CTRL_H__
