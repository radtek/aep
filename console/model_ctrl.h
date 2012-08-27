#include "stdafx.h"

#include "model2.h"
#include "draw_item_ctrl.h"

class CModelCtrl : public CStatic
{
public:
	CModelCtrl(Model2 &model);
	~CModelCtrl(void);
    void Init(CRect &rect);

    void SetRunItem(UINT32 id);
    void UnSetAllRunItem(bool invalidate);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

private:
    Model2 &m_Model;
    UINT32 m_Width, m_Height, m_VerMargin, m_HorMargin;
    UINT32 m_ComponentWidth, m_ComponentHeight;
    DrawItemCtrlList m_DrawItemCtrlList;

protected:
    void CalculateSize(CRect &rect);
    void CreateDrawItemCtrlList();

    void DrawDrawItemCtrlList(CDC *dc);
    void DrawConnectors(CDC *dc);
    void DrawConnector(CDC *dc, CPoint start, CPoint end);
    void DrawArrow(CDC *dc, CPoint start, CPoint end, double theta, UINT32 length);
};
