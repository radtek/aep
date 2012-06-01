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

    UINT32 id;
    ar >> id;

    m_InternalAlgorithm = &(theApp.m_Platform.GetInternalAlgorithmMap()[id]);
    m_InternalAlgorithm->Load(ar);

    m_Component = m_InternalAlgorithm;
}

void InternalAlgorithmCtrl::Export(CArchive &ar)
{
    ar << CCID_INTERNAL_ALGORITHM;
    m_InternalAlgorithm->Save(ar);
}

bool InternalAlgorithmCtrl::SetId(UINT32 id)
{
    return true;
}

void InternalAlgorithmCtrl::UpdateAttributeBar()
{
    CAttributeBar *attributeBar = GetAttributeBar();
    if (!attributeBar)
    {
        return;
    }
    attributeBar->SetInternalAlgorithm(m_InternalAlgorithm);
}

void InternalAlgorithmCtrl::ClearAttributeBar()
{
    CAttributeBar *attributeBar = GetAttributeBar();
    if (!attributeBar)
    {
        return;
    }
    attributeBar->Clear();
}
