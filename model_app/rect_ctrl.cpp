#include "rect_ctrl.h"

RectCtrl::RectCtrl(CPoint position)
:
m_Position(position)
{
}

RectCtrl::~RectCtrl()
{
}

void RectCtrl::OnDraw(CDC *dc)
{
    CPoint oldPosition = dc->MoveTo(m_Position);

    DrawBorder(dc);
    DrawTitle(dc);

    dc->MoveTo(oldPosition);
}

void RectCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (!HitTest(point))
    {
        if (m_IsSelected)
        {
            UnSelect();
        }
        return;
    }

    if (!m_IsSelected)
    {
        Select();
    }

    m_LastPosition = point;
}

void RectCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
    if (!(nFlags & MK_LBUTTON))
    {
        return;
    }
    if (m_IsSelected)
    {
        INT32 dx = point.x - m_LastPosition.x;
        INT32 dy = point.y - m_LastPosition.y;
        m_Position.x += dx;
        m_Position.y += dy;
        m_LastPosition = point;
    }
}

bool RectCtrl::HitTest(CPoint point)
{
    return point.x >= Left() &&
        point.x <= Right() &&
        point.y >= Top() &&
        point.y <= Bottom();
}

void RectCtrl::DrawBorder(CDC *dc)
{
    if (m_IsSelected)
    {
        CPen pen;
        pen.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
        CPen *oldPen = dc->SelectObject(&pen);
        dc->Rectangle(CRect(Left(), Top(), Right(), Bottom()));
        dc->SelectObject(oldPen);
    }
    else
    {
        dc->Rectangle(CRect(Left(), Top(), Right(), Bottom()));
    }
}

void RectCtrl::DrawTitle(CDC *dc)
{
    dc->TextOutW(Left(), Center().y, GetTitle().c_str());
}

INT32 RectCtrl::Left()
{
    return m_Position.x - s_Width / 2;
}

INT32 RectCtrl::Right()
{
    return m_Position.x + s_Width / 2;
}

INT32 RectCtrl::Top()
{
    return m_Position.y - s_Height / 2;
}

INT32 RectCtrl::Bottom()
{
    return m_Position.y + s_Height / 2;
}

CPoint RectCtrl::LeftTop()
{
    return CPoint(Left(), Top());
}

CPoint RectCtrl::LeftBottom()
{
    return CPoint(Left(), Bottom());
}

CPoint RectCtrl::RightTop()
{
    return CPoint(Right(), Top());
}

CPoint RectCtrl::RightBottom()
{
    return CPoint(Right(), Bottom());
}

CPoint RectCtrl::Center()
{
    return m_Position;
}

CPoint RectCtrl::LeftCenter()
{
    return CPoint(Left(), m_Position.y);
}

CPoint RectCtrl::RightCenter()
{
    return CPoint(Right(), m_Position.y);
}

CPoint RectCtrl::TopCenter()
{
    return CPoint(m_Position.x, Top());
}

CPoint RectCtrl::BottomCenter()
{
    return CPoint(m_Position.x, Bottom());
}

