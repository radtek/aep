#include "rect_ctrl.h"

RectCtrl::RectCtrl(CPoint position)
:
m_Position(position)
{
}

RectCtrl::~RectCtrl()
{
}

void RectCtrl::Draw(CDC *dc)
{
    CPoint oldPosition = dc->MoveTo(m_Position);

    DrawBorder(dc);
    DrawTitle(dc);

    dc->MoveTo(oldPosition);
}

bool RectCtrl::HitTest(CPoint point)
{
    return point.x >= Left() &&
        point.x <= Right() &&
        point.y >= Top() &&
        point.y <= Bottom();
}

void RectCtrl::Move(CPoint point)
{
    m_Position += point;
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

