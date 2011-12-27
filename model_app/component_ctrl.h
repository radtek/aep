/**
* @file
* @brief 组件控件类头文件.
* @author ruoxi
*
* 定义了组件控件类.
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
    virtual void Export(CArchive &ar);

    virtual bool Connect(ModelCtrl *modelCtrl);

    IComponent *GetComponent();

public:
    virtual UINT32 GetId();
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
