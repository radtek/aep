/**
* @file
* @brief 矩形控件类头文件.
* @author ruoxi
*
* 定义了矩形控件类.
*/

#ifndef __RECT_CTRL_H__
#define __RECT_CTRL_H__

#include "model_ctrl.h"
#include "interfaces.h"

class RectCtrl : public ModelCtrl
{
public:
    RectCtrl(CPoint position = CPoint(0, 0));
    virtual ~RectCtrl();

public:
    virtual void OnDraw(CDC *dc);
    virtual void OnLButtonDown(UINT nFlags, CPoint point);
    virtual void OnMouseMove(UINT nFlags, CPoint point);
    virtual bool HitTest(CPoint point);

    virtual wstring GetTitle() = 0;

protected:
    virtual void DrawBorder(CDC *dc);
    virtual void DrawTitle(CDC *dc);

public:
    virtual INT32 Left();
    virtual INT32 Right();
    virtual INT32 Top();
    virtual INT32 Bottom();

    virtual CPoint LeftTop();
    virtual CPoint LeftBottom();
    virtual CPoint RightTop();
    virtual CPoint RightBottom();
    virtual CPoint Center();
    virtual CPoint LeftCenter();
    virtual CPoint RightCenter();
    virtual CPoint TopCenter();
    virtual CPoint BottomCenter();

protected:
    CPoint m_Position;
    CPoint m_LastPosition;

protected:
    static const UINT32 s_Width = 100;
    static const UINT32 s_Height = 75;
};

#endif // __RECT_CTRL_H__
