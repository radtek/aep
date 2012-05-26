#include "model_ctrl.h"

#include <math.h>

CModelCtrl::CModelCtrl(Model &model)
: m_Model(model)
, m_Width(0)
, m_Height(0)
, m_VerMargin(0)
, m_HorMargin(0)
, m_ComponentWidth(0)
, m_ComponentHeight(0)
{
}

CModelCtrl::~CModelCtrl()
{
}

void CModelCtrl::Init(CRect &rect)
{
    CalculateSize(rect);
    CreateDrawItemCtrlList();
}

void CModelCtrl::SetRunItem(UINT32 id)
{
    UnSetAllRunItem(false);
    m_DrawItemCtrlList[id].SetRun(true);
    Invalidate();
}

void CModelCtrl::UnSetAllRunItem(bool invalidate)
{
    for (UINT32 i = 0; i < m_Model.GetAlgorithmCount(); ++i)
    {
        m_DrawItemCtrlList[i].SetRun(false);
    }
    if (invalidate)
    {
        Invalidate();
    }
}

BEGIN_MESSAGE_MAP(CModelCtrl, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CModelCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting

    DrawDrawItemCtrlList(&dc);
    DrawConnectors(&dc);
}

void CModelCtrl::CalculateSize(CRect &rect)
{
    m_Width = rect.Width();
    m_Height = rect.Height();

    m_HorMargin = m_Width / 10;
    m_VerMargin = m_Height / 3;

    UINT32 componentCount = m_Model.GetDrawItemList().size();
    m_ComponentWidth = (m_Width - (2 * m_HorMargin)) / (2 * componentCount - 1);
    m_ComponentHeight = m_Height - (2 * m_VerMargin);
}

void CModelCtrl::CreateDrawItemCtrlList()
{
    const DrawItemList &drawItemList = m_Model.GetDrawItemList();
    for (UINT32 i = 0; i < drawItemList.size(); ++i)
    {
        ::DrawItem *drawItem = drawItemList[i];
        CPoint position(m_HorMargin + 2 * i * m_ComponentWidth + m_ComponentWidth / 2, m_VerMargin + m_ComponentHeight / 2);
        DrawItemCtrl drawItemCtrl(position, m_ComponentWidth, m_ComponentHeight, drawItem);
        m_DrawItemCtrlList.push_back(drawItemCtrl);
    }
}

void CModelCtrl::DrawDrawItemCtrlList(CDC *dc)
{
    for (UINT32 i = 0; i < m_DrawItemCtrlList.size(); ++i)
    {
        m_DrawItemCtrlList[i].Draw(dc);
    }
}

void CModelCtrl::DrawConnectors(CDC *dc)
{
    for (UINT32 i = 0; i < m_DrawItemCtrlList.size() - 1; ++i)
    {
        CPoint start = m_DrawItemCtrlList[i].RightCenter();
        CPoint end = m_DrawItemCtrlList[i + 1].LeftCenter();
        DrawConnector(dc, start, end);
    }
}

void CModelCtrl::DrawConnector(CDC *dc, CPoint start, CPoint end)
{
    CPoint oldPosition = dc->MoveTo(start);

    dc->LineTo(end);

    DrawArrow(dc, start, end, 30, 7);

    dc->MoveTo(oldPosition);
}

void CModelCtrl::DrawArrow(CDC *dc, CPoint start, CPoint end, double theta, UINT32 length)
{
    double xx, yy, p1x, p1y, p2x, p2y;
    xx = start.x - end.x;
    yy = start.y - end.y;
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

    p1x = p1x + end.x;
    p1y = p1y + end.y;

    p2x = p2x + end.x;
    p2y = p2y + end.y;

    POINT triangle[3];
    triangle[0] = end;
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
