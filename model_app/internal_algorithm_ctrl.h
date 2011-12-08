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
    InternalAlgorithmCtrl(InternalAlgorithm *internalAlgorithm, CPoint position = CPoint(0, 0));
    virtual ~InternalAlgorithmCtrl();

public:
    virtual void UpdateAttributeBar();

protected:
    InternalAlgorithm *m_InternalAlgorithm;
};

#endif // __INTERNAL_ALGORITHM_CTRL_H__
