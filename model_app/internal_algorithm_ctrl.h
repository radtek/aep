/**
* @file
* @brief �ڲ��㷨�ؼ���ͷ�ļ�.
* @author ruoxi
*
* �������ڲ��㷨�ؼ���.
*/

#ifndef __INTERNAL_ALGORITHM_CTRL_H__
#define __INTERNAL_ALGORITHM_CTRL_H__

#include "component_ctrl.h"

#include "internal_algorithm.h"

class InternalAlgorithmCtrl : public ComponentCtrl
{
public:
    InternalAlgorithmCtrl(InternalAlgorithm *internalAlgorithm = NULL, CPoint position = CPoint(0, 0));
    virtual ~InternalAlgorithmCtrl();
 
    virtual void Save(CArchive &ar);
    virtual void Load(CArchive &ar);
    virtual void Export(CArchive &ar);

public:
    virtual bool SetId(UINT32 id);
    virtual void UpdateAttributeBar();
    virtual void ClearAttributeBar();

protected:
    InternalAlgorithm *m_InternalAlgorithm;

public:
    static const UINT32 s_ModelCtrlId = 1;
};

#endif // __INTERNAL_ALGORITHM_CTRL_H__
