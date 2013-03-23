#include "stdafx.h"
#include "model_app.h"

#include "model_ctrl.h"
#include "connector_ctrl.h"
#include "ver_poly_connector_ctrl.h"

#include "utility.h"

VerPolyConnectorCtrl::VerPolyConnectorCtrl(CPoint point)
:
ConnectorCtrl(point)
{
    m_End.y += s_Length;
}

VerPolyConnectorCtrl::~VerPolyConnectorCtrl()
{
}

UINT32 VerPolyConnectorCtrl::GetTypeId()
{
    return ID_VER_POLY_CONNECTOR;
}

void VerPolyConnectorCtrl::Draw(CDC *dc)
{
    CPoint oldPosition = dc->MoveTo(m_Start);

    CPoint center1, center2;
    center1.x = m_Start.x;
    center2.x = m_End.x;
    center1.y = center2.y = (m_Start.y + m_End.y) / 2;

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

double VerPolyConnectorCtrl::Distance(CPoint point)
{
    CPoint center1, center2;
    center1.x = m_Start.x;
    center2.x = m_End.x;
    center1.y = center2.y = (m_Start.y + m_End.y) / 2;

    return min(Utility::DistanceToEdge(m_Start, center1, point), min(Utility::DistanceToEdge(center1, center2, point), Utility::DistanceToEdge(center2, m_End, point)));
}
