/**
* @file
* @brief ģ�Ϳؼ���ͷ�ļ�.
* @author ruoxi
*
* ������ģ�Ϳؼ���.
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
    virtual void OnDraw(CDC *dc) = 0;
    virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
    virtual void OnMouseMove(UINT nFlags, CPoint point) = 0;
    virtual bool HitTest(CPoint point) = 0;
    virtual bool SetId(UINT32 id) = 0;

protected:
    virtual void Select();
    virtual void UnSelect();
    virtual bool IsSelected();

    virtual COutputBar &GetOutputBar();
    virtual void UpdateOutputBar() = 0;
    virtual void ClearOutputBar() = 0;

protected:
    bool m_IsSelected;
};

typedef list<ModelCtrl *> ModelCtrlList;

#endif // __MODEL_CTRL_H__
