#include "stdafx.h"
#include "model_app.h"

#include "model_ctrl.h"
#include "connector_ctrl.h"
#include "hor_poly_connector_ctrl.h"

#include "utility.h"

HorPolyConnectorCtrl::HorPolyConnectorCtrl(CPoint point)
:
ConnectorCtrl(point)
{
    m_End.y += s_Length;
}

HorPolyConnectorCtrl::~HorPolyConnectorCtrl()
{
}

UINT32 HorPolyConnectorCtrl::GetTypeId()
{
    return ID_HOR_POLY_CONNECTOR;
}

void HorPolyConnectorCtrl::Draw(CDC *dc)
{
    CPoint oldPosition = dc->MoveTo(m_Start);

    CPoint center1, center2;
    center1.x = center2.x = (m_Start.x + m_End.x) / 2;
    center1.y = m_Start.y;
    center2.y = m_End.y;

    if (m_CurrentSelectMode != CSM_NONE)
    {
        CPen pen;
        pen.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
        CPen *oldPen = dc->SelectObject(&pen);
        dc->LineTo(center1);
        dc->LineTo(center2);
        dc->LineTo(m_End);
        dc->SelectObject(oldPen);
    }
    else
    {
        dc->LineTo(center1);
        dc->LineTo(center2);
        dc->LineTo(m_End);
    }

    DrawArrow(dc, center2, m_End, 30, 7);

    dc->MoveTo(oldPosition);
}

double HorPolyConnectorCtrl::Distance(CPoint point)
{
    CPoint center1, center2;
    center1.x = center2.x = (m_Start.x + m_End.x) / 2;
    center1.y = m_Start.y;
    center2.y = m_End.y;

    return min(Utility::DistanceToEdge(m_Start, center1, point), min(Utility::DistanceToEdge(center1, center2, point), Utility::DistanceToEdge(center2, m_End, point)));
}
