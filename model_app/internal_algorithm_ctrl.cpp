#include "stdafx.h"
#include "model_app.h"

#include "attribute_bar.h"

#include "internal_algorithm_ctrl.h"

InternalAlgorithmCtrl::InternalAlgorithmCtrl(InternalAlgorithm *internalAlgorithm, CPoint position)
:
ComponentCtrl(internalAlgorithm, position),
m_InternalAlgorithm(internalAlgorithm)
{
}

InternalAlgorithmCtrl::~InternalAlgorithmCtrl()
{
    m_InternalAlgorithm->Destroy();
}

void InternalAlgorithmCtrl::UpdateAttributeBar()
{
    GetAttributeBar().SetInternalAlgorithm(m_InternalAlgorithm);
}
