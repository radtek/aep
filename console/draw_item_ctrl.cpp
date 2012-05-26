#include "draw_item_ctrl.h"

DrawItemCtrl::DrawItemCtrl(CPoint position, UINT32 width, UINT32 height, DrawItem *drawItem)
: m_Position(position)
, m_Width(width)
, m_Height(height)
, m_DrawItem(drawItem)
, m_IsRunning(false)
{
}

DrawItemCtrl::~DrawItemCtrl()
{
}

void DrawItemCtrl::Draw(CDC *dc)
{
    DrawBorder(dc);
    DrawTitle(dc);
}

void DrawItemCtrl::SetRun(bool run)
{
    m_IsRunning = run;
}

void DrawItemCtrl::DrawBorder(CDC *dc)
{
    CPoint oldPosition = dc->MoveTo(m_Position);

    if (m_IsRunning)
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

    dc->MoveTo(oldPosition);
}

void DrawItemCtrl::DrawTitle(CDC *dc)
{
    dc->TextOutW(Left(), Center().y, m_DrawItem->GetName().c_str());
}

INT32 DrawItemCtrl::Left()
{
    return m_Position.x - m_Width / 2;
}

INT32 DrawItemCtrl::Right()
{
    return m_Position.x + m_Width / 2;
}

INT32 DrawItemCtrl::Top()
{
    return m_Position.y - m_Height / 2;
}

INT32 DrawItemCtrl::Bottom()
{
    return m_Position.y + m_Height / 2;
}

CPoint DrawItemCtrl::Center()
{
    return m_Position;
}

CPoint DrawItemCtrl::LeftCenter()
{
    return CPoint(Left(), m_Position.y);
}

CPoint DrawItemCtrl::RightCenter()
{
    return CPoint(Right(), m_Position.y);
}

CPoint DrawItemCtrl::TopCenter()
{
    return CPoint(m_Position.x, Top());
}

CPoint DrawItemCtrl::BottomCenter()
{
    return CPoint(m_Position.x, Bottom());
}

CPoint DrawItemCtrl::LeftTop()
{
    return CPoint(Left(), Top());
}

CPoint DrawItemCtrl::LeftBottom()
{
    return CPoint(Left(), Bottom());
}

CPoint DrawItemCtrl::RightTop()
{
    return CPoint(Right(), Top());
}

CPoint DrawItemCtrl::RightBottom()
{
    return CPoint(Right(), Bottom());
}
