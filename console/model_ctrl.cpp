#include "model_ctrl.h"

CModelCtrl::CModelCtrl(Model &model)
: m_Model(model)
, m_Width(800)
, m_Height(600)
{
}

CModelCtrl::~CModelCtrl()
{
}

BEGIN_MESSAGE_MAP(CModelCtrl, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CModelCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
    dc.SetBkColor(RGB(255, 255, 255));
    dc.LineTo(100, 100);
}
