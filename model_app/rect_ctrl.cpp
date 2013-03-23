#include "stdafx.h"
#include "model_app.h"

#include "rect_ctrl.h"

#include "connector_ctrl.h"

#include "utility.h"

#include <algorithm>

using namespace std;

RectCtrl::RectCtrl(CPoint position)
:
m_Position(position),
m_Color(RGB(255, 255, 255))
{
}

RectCtrl::~RectCtrl()
{
}

void RectCtrl::Save(CArchive &ar)
{
    ar << m_Position;
}

void RectCtrl::Load(CArchive &ar)
{
    ar >> m_Position;
}

void RectCtrl::Draw(CDC *dc)
{
    CPoint oldPosition = dc->MoveTo(m_Position);

    DrawRect(dc);
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
    for (list<ConnectorCtrl *>::iterator it = m_ConnectorCtrlList.begin();
        it != m_ConnectorCtrlList.end(); ++it)
    {
        (*it)->Move(point, this);
    }
}

void RectCtrl::DrawRect(CDC *dc)
{
    CBrush brush;
    brush.CreateSolidBrush(m_Color);
    CBrush *oldBrush = dc->SelectObject(&brush);

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

    dc->SelectObject(oldBrush);
}

void RectCtrl::DrawTitle(CDC *dc)
{
    COLORREF oldColor = dc->SetBkColor(m_Color);

    CFont font;
    // font.CreatePointFont(90, TEXT("Î¢ÈíÑÅºÚ"));
    font.CreateFont(16, 0, 0, 0, m_IsSelected ? FW_BOLD : FW_NORMAL,
        FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
        TEXT("Î¢ÈíÑÅºÚ"));
    CFont *pOldFont = (CFont *)dc->SelectObject(&font);

    CSize sz = dc->GetTextExtent(GetTitle().c_str());
    if (sz.cx > s_Width - 2 * s_Margin)
    {
        sz.cx = s_Width - 2 * s_Margin;
    }

    UINT32 startX = Left() + s_Margin + (s_Width - 2 * s_Margin - sz.cx) / 2;
    UINT32 startY = Top() + (s_Height - sz.cy) / 2;

    // dc->TextOutW(startX, startY, GetTitle().c_str());
    dc->DrawText(GetTitle().c_str(), CRect(startX, startY, startX + sz.cx, startY + sz.cy), 0);

    dc->SelectObject(pOldFont);
    dc->SetBkColor(oldColor);
}

CPoint RectCtrl::GetAttachPoint(CPoint point)
{
    enum EDGE
    {
        LEFT = 0,
        DOWN,
        RIGHT,
        UP,
        SIZE,
    };
    UINT32 distance[SIZE];
    distance[LEFT] = Utility::DistanceToEdge(LeftTop(), LeftBottom(), point);
    distance[DOWN] = Utility::DistanceToEdge(LeftBottom(), RightBottom(), point);
    distance[RIGHT] = Utility::DistanceToEdge(RightTop(), RightBottom(), point);
    distance[UP] = Utility::DistanceToEdge(LeftTop(), RightTop(), point);

    UINT32 *m = min_element(&distance[LEFT], &distance[SIZE]);
    EDGE edge = EDGE(m - &distance[LEFT]);

    switch (edge)
    {
    case LEFT:
        point.x = Left();
        break;
    case DOWN:
        point.y = Bottom();
        break;
    case RIGHT:
        point.x = Right();
        break;
    case UP:
        point.y = Top();
        break;
    }

    return point;
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
