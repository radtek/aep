#include "stdafx.h"
#include "model_app.h"

#include "model_ctrl.h"
#include "connector.h"

#include "model_doc.h"

#include "utility.h"
#include "massert.h"

Connector::Connector(CPoint point)
:
m_Start(point.x - s_Length / 2, point.y),
m_End(point.x + s_Length / 2, point.y),
m_CurrentSelectMode(CSM_NONE),
m_Source(NULL),
m_Target(NULL)
{
}

Connector::~Connector()
{
}
void Connector::Save(CArchive &ar)
{
    ar << m_Start
        << m_End;

    ar << m_Source->GetId()
        << m_Target->GetId();
}

void Connector::Load(CArchive &ar, CModelDoc &doc)
{
    ar >> m_Start
        >> m_End;

    UINT32 sourceId, targetId;
    ar >> sourceId
        >> targetId;
    
    for (ModelCtrlList::iterator it = doc.m_ModelCtrlList.begin();
        it != doc.m_ModelCtrlList.end(); ++it)
    {
        ModelCtrl *modelCtrl = (*it);
        if (modelCtrl->GetId() == sourceId)
        {
            m_Source = modelCtrl;
            m_Source->AddConnector(this);
        }
        else if (modelCtrl->GetId() == targetId)
        {
            m_Target = modelCtrl;
            m_Target->AddConnector(this);
        }
    }
}

void Connector::Draw(CDC *dc)
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

    dc->MoveTo(oldPosition);
}

Connector::ConnectorSelectMode Connector::HitTest(CPoint point)
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

void Connector::Select(ConnectorSelectMode selectMode)
{
    m_CurrentSelectMode = selectMode;
}

Connector::ConnectorSelectMode Connector::GetSelectMode()
{
    return m_CurrentSelectMode;
}

void Connector::Move(CPoint point, ModelCtrl *from)
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

void Connector::Connect(ModelCtrl *modelCtrl)
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
        m_Source->AddConnector(this);
        return;
    }

    if (m_CurrentSelectMode == CSM_END)
    {
        m_Target = modelCtrl;
        m_Target->AddConnector(this);
        return;
    }
}

void Connector::Disconnect()
{
    if (m_CurrentSelectMode == CSM_NONE)
    {
        return;
    }

    if (m_CurrentSelectMode == CSM_ALL)
    {
        if (m_Source != NULL)
        {
            m_Source->RemoveConnector(this);
            m_Source = NULL;
        }
        if (m_Target != NULL)
        {
            m_Target->RemoveConnector(this);
            m_Target = NULL;
        }
        return;
    }

    if (m_CurrentSelectMode == CSM_START)
    {
        if (m_Source != NULL)
        {
            m_Source->RemoveConnector(this);
            m_Source = NULL;
        }
        return;
    }

    if (m_CurrentSelectMode == CSM_END)
    {
        if (m_Target != NULL)
        {
            m_Target->RemoveConnector(this);
            m_Target = NULL;
        }
        return;
    }
}

void Connector::SetAttachPoint(CPoint point)
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

bool Connector::Connect()
{
    return m_Source->Connect(m_Target);
}

bool Connector::InBound(CPoint point)
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

double Connector::Distance(CPoint point)
{
    return Utility::DistanceToEdge(m_Start, m_End, point);
}

double Connector::DistanceToStart(CPoint point)
{
    return Utility::DistanceToPoint(m_Start, point);
}

double Connector::DistanceToEnd(CPoint point)
{
    return Utility::DistanceToPoint(m_End, point);
}
