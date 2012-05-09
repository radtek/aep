#include "stdafx.h"
#include "model_app.h"

#include "model_ctrl.h"
#include "connector_ctrl.h"

#include "model_doc.h"

#include "utility.h"
#include "massert.h"

#include <math.h>

ConnectorCtrl::ConnectorCtrl(CPoint point)
:
m_Start(point.x - s_Length / 2, point.y),
m_End(point.x + s_Length / 2, point.y),
m_CurrentSelectMode(CSM_NONE),
m_Source(NULL),
m_Target(NULL)
{
}

ConnectorCtrl::~ConnectorCtrl()
{
}

void ConnectorCtrl::Save(CArchive &ar)
{
    ar << m_Start
        << m_End;

    ar << (m_Source != NULL ? TRUE : FALSE)
        << (m_Target != NULL ? TRUE : FALSE);

    ar << (m_Source != NULL ? m_Source->GetId() : 0)
        << (m_Target != NULL ? m_Target->GetId() : 0);
}

void ConnectorCtrl::Load(CArchive &ar, CModelDoc &doc)
{
    ar >> m_Start
        >> m_End;

    BOOL sourceValid, targetValid;
    ar >> sourceValid >> targetValid;

    UINT32 sourceId, targetId;
    ar >> sourceId
        >> targetId;
    
    for (ModelCtrlList::iterator it = doc.m_ModelCtrlList.begin();
        it != doc.m_ModelCtrlList.end(); ++it)
    {
        ModelCtrl *modelCtrl = (*it);
        if (sourceValid && modelCtrl->GetId() == sourceId)
        {
            m_Source = modelCtrl;
            m_Source->AddConnectorCtrl(this);
        }
        if (targetValid && modelCtrl->GetId() == targetId)
        {
            m_Target = modelCtrl;
            m_Target->AddConnectorCtrl(this);
        }
    }
}

void ConnectorCtrl::Export(CArchive &ar)
{
    ar << (m_Source != NULL ? TRUE : FALSE)
        << (m_Target != NULL ? TRUE : FALSE);

    ar << (m_Source != NULL ? m_Source->GetId() : 0)
        << (m_Target != NULL ? m_Target->GetId() : 0);
}

ModelCtrl *ConnectorCtrl::GetSource()
{
    return m_Source;
}

ModelCtrl *ConnectorCtrl::GetTarget()
{
    return m_Target;
}

void ConnectorCtrl::Draw(CDC *dc)
{
    CPoint oldPosition = dc->MoveTo(m_Start);

    if (m_CurrentSelectMode != CSM_NONE)
    {
        CPen pen;
        pen.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
        CPen *oldPen = dc->SelectObject(&pen);
        dc->LineTo(m_End);
        dc->SelectObject(oldPen);
    }
    else
    {
        dc->LineTo(m_End);
    }

    DrawArrow(dc, 30, 7);

    dc->MoveTo(oldPosition);
}

void ConnectorCtrl::DrawArrow(CDC *dc, double theta, UINT32 length)
{
    double xx, yy, p1x, p1y, p2x, p2y;
    xx = m_Start.x - m_End.x;
    yy = m_Start.y - m_End.y;
    theta = 3.1415926 * theta / 180;
    p1x = xx * cos(theta) - yy * sin(theta);
    p1y = xx * sin(theta) + yy * cos(theta);
    p2x = xx * cos(theta) + yy * sin(theta);
    p2y = xx * sin(-theta) + yy * cos(theta);

    double p1, p2;
    p1 = sqrt(p1x * p1x + p1y * p1y);
    p2 = sqrt(p2x * p2x + p2y * p2y);

    p1x = p1x * length / p1;
    p1y = p1y * length / p1;
    p2x = p2x * length / p2;
    p2y = p2y * length / p2;

    p1x = p1x + m_End.x;
    p1y = p1y + m_End.y;

    p2x = p2x + m_End.x;
    p2y = p2y + m_End.y;

    POINT triangle[3];
    triangle[0] = m_End;
    triangle[1].x = p1x + 0.5;
    triangle[1].y = p1y + 0.5;
    triangle[2].x = p2x + 0.5;
    triangle[2].y = p2y + 0.5;

    CBrush brush;
    brush.CreateSolidBrush(RGB(0, 0, 0));
    CBrush *oldBrush = dc->SelectObject(&brush);
    dc->Polygon(&triangle[0], 3);
    dc->SelectObject(oldBrush);
}

ConnectorCtrl::ConnectorCtrlSelectMode ConnectorCtrl::HitTest(CPoint point)
{
    if (m_CurrentSelectMode == SM_NONE)
    {
        if (InBound(point) && Distance(point) <= s_Threshold)
        {
            return CSM_ALL;
        }
        else
        {
            return CSM_NONE;
        }
    }
    else
    {
        if (DistanceToStart(point) <= s_Threshold)
        {
            return CSM_START;
        }
        else if (DistanceToEnd(point) <= s_Threshold)
        {
            return CSM_END;
        }
        else if (InBound(point) && Distance(point) <= s_Threshold)
        {
            return CSM_ALL;
        }
        else
        {
            return CSM_NONE;
        }
    }
}

void ConnectorCtrl::Select(ConnectorCtrlSelectMode selectMode)
{
    m_CurrentSelectMode = selectMode;
}

ConnectorCtrl::ConnectorCtrlSelectMode ConnectorCtrl::GetSelectMode()
{
    return m_CurrentSelectMode;
}

void ConnectorCtrl::Move(CPoint point, ModelCtrl *from)
{
    if (from != NULL)
    {
        MASSERT(m_CurrentSelectMode == CSM_NONE);
        if (from == m_Source)
        {
            m_Start += point;
        }
        else if (from == m_Target)
        {
            m_End += point;
        }
        return;
    }

    if (m_CurrentSelectMode == CSM_NONE)
    {
        return;
    }

    if (m_CurrentSelectMode == CSM_ALL)
    {
        m_Start += point;
        m_End += point;
        return;
    }

    if (m_CurrentSelectMode == CSM_START)
    {
        m_Start += point;
        return;
    }

    if (m_CurrentSelectMode == CSM_END)
    {
        m_End += point;
        return;
    }
}

void ConnectorCtrl::Connect(ModelCtrl *modelCtrl)
{
    if (m_CurrentSelectMode == CSM_NONE)
    {
        return;
    }

    if (m_CurrentSelectMode == CSM_ALL)
    {
        return;
    }

    if (m_CurrentSelectMode == CSM_START)
    {
        m_Source = modelCtrl;
        m_Source->AddConnectorCtrl(this);
        return;
    }

    if (m_CurrentSelectMode == CSM_END)
    {
        m_Target = modelCtrl;
        m_Target->AddConnectorCtrl(this);
        return;
    }
}

void ConnectorCtrl::Disconnect()
{
    if (m_CurrentSelectMode == CSM_NONE)
    {
        return;
    }

    if (m_CurrentSelectMode == CSM_ALL)
    {
        if (m_Source != NULL)
        {
            m_Source->RemoveConnectorCtrl(this);
            m_Source = NULL;
        }
        if (m_Target != NULL)
        {
            m_Target->RemoveConnectorCtrl(this);
            m_Target = NULL;
        }
        return;
    }

    if (m_CurrentSelectMode == CSM_START)
    {
        if (m_Source != NULL)
        {
            m_Source->RemoveConnectorCtrl(this);
            m_Source = NULL;
        }
        return;
    }

    if (m_CurrentSelectMode == CSM_END)
    {
        if (m_Target != NULL)
        {
            m_Target->RemoveConnectorCtrl(this);
            m_Target = NULL;
        }
        return;
    }
}

void ConnectorCtrl::SetAttachPoint(CPoint point)
{
    if (m_CurrentSelectMode == CSM_START)
    {
        m_Start = point;
    }
    else if (m_CurrentSelectMode == CSM_END)
    {
        m_End = point;
    }
}

/*
bool ConnectorCtrl::Connect()
{
    return m_Source->Connect(m_Target);
}
*/

bool ConnectorCtrl::InBound(CPoint point)
{
    INT32 left = min(m_Start.x, m_End.x) - s_Threshold,
        right = max(m_Start.x, m_End.x) + s_Threshold,
        up = min(m_Start.y, m_End.y) - s_Threshold,
        down = max(m_Start.y, m_End.y) + s_Threshold;

    return
        point.x >= left &&
        point.x <= right &&
        point.y >= up &&
        point.y <= down;
}

double ConnectorCtrl::Distance(CPoint point)
{
    return Utility::DistanceToEdge(m_Start, m_End, point);
}

double ConnectorCtrl::DistanceToStart(CPoint point)
{
    return Utility::DistanceToPoint(m_Start, point);
}

double ConnectorCtrl::DistanceToEnd(CPoint point)
{
    return Utility::DistanceToPoint(m_End, point);
}
