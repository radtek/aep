#include "stdafx.h"
#include "model_app.h"
#include "attribute_grid_ctrl.h"

#include "attribute_bar.h"

CAttributeGridCtrl::CAttributeGridCtrl(CAttributeBar *attributeBar)
:
m_AttributeBar(attributeBar)
{
}

void CAttributeGridCtrl::OnItemChanged(CBCGPGridItem* pItem, int nRow, int nColumn)
{
    m_AttributeBar->OnItemChanged(pItem, nRow, nColumn);
}
