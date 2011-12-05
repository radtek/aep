/**
* @file
* @brief 模型控件类头文件.
* @author ruoxi
*
* 定义了模型控件类.
*/

#ifndef __MODEL_CTRL_H__
#define __MODEL_CTRL_H__

#include <afxwin.h>

#include <list>

#include "stdafx.h"
#include "model_app.h"
#include "main_frm.h"

using namespace std;

class ModelCtrl
{
public:
    ModelCtrl();
    virtual ~ModelCtrl();

public:
    virtual void Draw(CDC *dc) = 0;
    virtual bool HitTest(CPoint point) = 0;
    virtual bool SetId(UINT32 id) = 0;
    virtual void Move(CPoint point) = 0;

    virtual void Select();
    virtual void UnSelect();

protected:
    virtual CAttributeBar &GetAttributeBar();
    virtual void UpdateAttributeBar() = 0;
    virtual void ClearAttributeBar() = 0;

protected:
    bool m_IsSelected;
};

typedef list<ModelCtrl *> ModelCtrlList;

#endif // __MODEL_CTRL_H__
