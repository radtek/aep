/**
* @file
* @brief 矩形控件类头文件.
* @author ruoxi
*
* 定义了矩形控件类.
*/

#ifndef __DRAW_ITEM_CTRL_H__
#define __DRAW_ITEM_CTRL_H__

#include "stdafx.h"
#include "model.h"

class DrawItemCtrl
{
public:
    DrawItemCtrl(CPoint position, UINT32 width, UINT32 height, DrawItem *drawItem);
    virtual ~DrawItemCtrl();

public:
    virtual void Draw(CDC *dc);
    virtual void SetRun(bool run);

protected:
    virtual void DrawBorder(CDC *dc);
    virtual void DrawTitle(CDC *dc);

public:
    virtual INT32 Left();
    virtual INT32 Right();
    virtual INT32 Top();
    virtual INT32 Bottom();

    virtual CPoint Center();
    virtual CPoint LeftCenter();
    virtual CPoint RightCenter();
    virtual CPoint TopCenter();
    virtual CPoint BottomCenter();

    virtual CPoint LeftTop();
    virtual CPoint LeftBottom();
    virtual CPoint RightTop();
    virtual CPoint RightBottom();

protected:
    CPoint m_Position;
    UINT32 m_Width, m_Height;

    bool m_IsRunning;

    DrawItem *m_DrawItem;

private:
    const static COLORREF s_RunningBkg = RGB(0.618 * 256, 0.618 * 256, 0.618 * 256);
};

typedef vector<DrawItemCtrl> DrawItemCtrlList;

#endif // __DRAW_ITEM_CTRL_H__
