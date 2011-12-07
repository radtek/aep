#include "stdafx.h"
#include "model_app.h"

#include "rect_ctrl.h"

#include "connector.h"

#include "utility.h"

#include <algorithm>

using namespace std;

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
    for (list<Connector *>::iterator it = m_ConnectorList.begin();
        it != m_ConnectorList.end(); ++it)
    {
        (*it)->Move(point, this);
    }
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
