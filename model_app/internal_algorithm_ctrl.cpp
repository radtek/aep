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

void InternalAlgorithmCtrl::Save(CArchive &ar)
{
    ar << s_ModelCtrlId;

    RectCtrl::Save(ar);

    m_InternalAlgorithm->Save(ar);
}

void InternalAlgorithmCtrl::Load(CArchive &ar)
{
    RectCtrl::Load(ar);

    UINT32 algorithmId;
    ar >> algorithmId;

    m_InternalAlgorithm = &(theApp.m_Platform.GetInternalAlgorithmMap()[algorithmId]);
    m_InternalAlgorithm->Load(ar);

    m_Component = m_InternalAlgorithm;
}

void InternalAlgorithmCtrl::UpdateAttributeBar()
{
    GetAttributeBar().SetInternalAlgorithm(m_InternalAlgorithm);
}
